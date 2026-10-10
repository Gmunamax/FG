#include <engine/utils/player.hpp>
#include <random.hpp>
#include "../office.hpp"

class TB1ai{
public:
	TB1ai(Model& tb1Model):
		model{tb1Model}
	{}

	void Update(Player::TimeType timeDelta){
		action = (this->*action)(timeDelta).nextAction;
	}

private:
	struct NextAction;

	using Action = NextAction(TB1ai::*)(Player::TimeType);

	struct NextAction{
		Action nextAction;

		NextAction& operator=(Action newAction){
			nextAction = newAction;
			return *this;
		}
	};

	NextAction MakeNewAction(Player::TimeType timeDelta){
		OfficeGraph::LocationsEnum currentLocation = OfficeGraph::GetNearestLocation(model.GetPosition());
		NextAction newAction;
		switch(currentLocation){
		using enum OfficeGraph::LocationsEnum;
		case BehindTheFrontDoor:
			newAction = &TB1ai::EnterFrontDoor;
			break;

		default:
			newAction = &TB1ai::GoToRandomExit;
			break;
		}
		return newAction;
	}

	NextAction GoToRandomExit(Player::TimeType){
		path = pathFinder.FindPath(OfficeGraph::GetNearestLocation(model.GetPosition()), GetRandomExit());
		return {&TB1ai::FollowPath};
	}

	OfficeGraph::LocationsEnum GetRandomExit(){
		enum class AvaliableExit{
			ToDoor1,
			ToDoor2,
			ToBackDoor,
			Min = ToDoor1,
			Max = ToBackDoor
		};

		AvaliableExit action = (AvaliableExit)Random::GetRandomNumber((Random::RandomType)AvaliableExit::Min, (Random::RandomType)AvaliableExit::Max);
		OfficeGraph::LocationsEnum exit;
		switch(action){
		using enum AvaliableExit;
		case ToDoor1:
			exit = OfficeGraph::LocationsEnum::BehindTheFrontDoor;
			break;

		case ToDoor2:
			exit = OfficeGraph::LocationsEnum::BehindTheSideDoor;
			break;

		case ToBackDoor:
			exit = OfficeGraph::LocationsEnum::FarAway;
			break;
		}
		return exit;
	}

	NextAction FollowPath(Player::TimeType timeDelta){
		static Player::TimeType timePassed = 0;
		if(timePassed < 1){
			timePassed += timeDelta;
		}
		else{
			timePassed = 0;

			if(path.empty()){
				return {&TB1ai::MakeNewAction};
			}
			else{
				model.SetPosition(OfficeGraph::GetLocationPosition((OfficeGraph::LocationsEnum)path.front()));
				path.pop();
			}
		}
		return {&TB1ai::FollowPath};
	}

	NextAction EnterFrontDoor(Player::TimeType timeDelta){
		TeleportToRandom();
		return {&TB1ai::MakeNewAction};
	}

	void TeleportToRandom(){
		OfficeGraph::LocationsEnum randomNumber = (OfficeGraph::LocationsEnum)Random::GetRandomNumber(0, 6);
		model.SetPosition(OfficeGraph::GetLocationPosition(randomNumber));
	}

	PathFinder::PathFinder pathFinder{Office::GenGraph()};
	Action action = &TB1ai::MakeNewAction;
	PathFinder::PathFinder::Path path;
	Model& model;
};
