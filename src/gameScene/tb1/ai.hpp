#include <random>
#include <print>
#include <engine/utils/player.hpp>
#include "../office.hpp"

class TB1ai{
public:
	TB1ai(Model& tb1Model):
		model{tb1Model}
	{}

	void Update(Player::TimeType timeDelta){
		(this->*action)(timeDelta);
	}

private:
	template<typename Type>
	Type GetRandomNumber(Type min, Type max){
		std::random_device random;
		std::mt19937 generator(random());
		std::uniform_int_distribution<>	distribution{min, max};
		return distribution(generator);
	}

	enum class PossibleAction{
		ToDoor1,
		ToDoor2,
		ToBackDoor,
		Min = ToDoor1,
		Max = ToBackDoor
	};

	void MakeNewAction(Player::TimeType timeDelta){
		PossibleAction action = (PossibleAction)GetRandomNumber((int)PossibleAction::Min, (int)PossibleAction::Max);
		const char* actionString = "Unknown";
		switch(action){
		case PossibleAction::ToDoor1:
			actionString = "To door 1";
			path = pathFinder.FindPath(OfficeGraph::GetNearestLocation(model.GetPosition()), OfficeGraph::LocationsEnum::BehindTheFrontDoor);
			this->action = &TB1ai::FollowPath;
			break;

		case PossibleAction::ToDoor2:
			actionString = "To door 2";
			path = pathFinder.FindPath(OfficeGraph::GetNearestLocation(model.GetPosition()), OfficeGraph::LocationsEnum::NearTheSideDoor);
			this->action = &TB1ai::FollowPath;
			break;

		case PossibleAction::ToBackDoor:
			actionString = "To back door";
			path = pathFinder.FindPath(OfficeGraph::GetNearestLocation(model.GetPosition()), OfficeGraph::LocationsEnum::FarAway);
			this->action = &TB1ai::FollowPath;
			break;
		}
		std::println("new action: {}", actionString);
	}

	void FollowPath(Player::TimeType timeDelta){
		static Player::TimeType timePassed = 0;
		if(timePassed < 1){
			timePassed += timeDelta;
			return;
		}
		else{
			timePassed = 0;

			if(path.empty()){
				this->action = &TB1ai::MakeNewAction;
				return;
			}
			else{
				model.SetPosition(OfficeGraph::GetLocationPosition((OfficeGraph::LocationsEnum)path.front()));
				path.pop();
			}
		}
	}

	void(TB1ai::* action)(Player::TimeType) = &TB1ai::MakeNewAction;
	PathFinder::PathFinder pathFinder{Office::GenGraph()};
	PathFinder::PathFinder::Path path;
	Model& model;
};
