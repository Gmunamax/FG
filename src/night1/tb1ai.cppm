module;
#include <engine/utils/player.hpp>
#include <engine/utils/properties/timer.hpp>
#include <print>
#include <random>

export module Night1:TB1ai;

namespace Night1{

	class TB1ai{
	public:
		TB1ai(){
			BeginWaiting();
		}

		void Update(){
			(this->*action)();
		}

	private:
		void WaitForAttack(){
			if(timer.GetTime() > attackDelay){
				BeginAttack();
			}
			else{
				// wait for next iteration
			}
		}

		void Attack(){
			const Player::TimeType timeToEvade = 5;

			if(timer.GetTime() > timeToEvade){
				bool evaded = false;
				if(!evaded){
					std::println("Looks like YGIO");
				}

				BeginWaiting();
			}
			else{
				// wait for next iteration
			}
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

		Action action;
		Timer timer;
		Player::TimeType attackDelay;
		unsigned attacks = 0;
	};

}
