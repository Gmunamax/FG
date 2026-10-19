module;
#include <engine/utils/player.hpp>
#include <engine/utils/properties/timer.hpp>
#include <print>
#include <random>

export module Night1:TB1ai;
import :Door;
import :Time;

namespace Night1{

	class TB1ai{
	public:
		TB1ai(Door* door, Time* time):
			door{door},
			time{time}
		{
			Reset();
		}

		void Update(){
			(this->*action)();
		}

	private:
		void WaitForAttack(){
			TestEndTime();
			if(timer.GetTime() > attackDelay){
				BeginAttack();
			}
			else{
				// wait for next iteration
			}
		}

		void Attack(){
			const Player::TimeType timeToEvade = 5;

			TestEndTime();
			if(timer.GetTime() > timeToEvade){
				if(!IsEvading()){
					HuntPlayer();
				}
				else{
					std::println("I'll get you");
				}

				BeginWaiting();
			}
			else{
				// wait for next iteration
			}
		}

		void TestEndTime(){
			if(time->GetTime() >= time->GetEndTime()){
				action = &TB1ai::EndTime;
			}
		}

		void EndTime(){
			std::println("Congratulations. Next time I'll get you...");
			action = &TB1ai::NoopAfterEndTime;
		}

		void NoopAfterEndTime(){
			
		}

		void HuntPlayer(){
			std::println("I got you. YGIO");
			Reset();
		}

		void Reset(){
			time->ResetTimer();
			attacks = 0;
			BeginWaiting();
		}

		template<typename Type>
		Type GetRandomNumber(Type min, Type max){
			std::random_device random;
			std::mt19937 generator(random());
			std::uniform_int_distribution<>	distribution{min, max};
			return distribution(generator);
		}

		using Action = void(TB1ai::*)();

		void BeginWaiting(){
			attackDelay = GetRandomNumber(50, 75);
			action = &TB1ai::WaitForAttack;
			timer.Reset();
		}
	
		void BeginAttack(){
			++attacks;
			std::println("Begining attack");
			action = &TB1ai::Attack;
			timer.Reset();
		}

		bool IsEvading(){
			if(door->GetClosed()){
				return true;
			}
			else{
				return false;
			}
		}

		Action action;
		Timer timer;
		Player::TimeType attackDelay;
		unsigned attacks = 0;
		Door* door;
		Time* time;
	};

}
