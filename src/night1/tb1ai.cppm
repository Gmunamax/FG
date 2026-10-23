// FG - a horror game
// Copyright (C) 2026 Gmunamax <https://github.com/Gmunamax/FG>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
module;
#include <FGengine/utils/timer.hpp>
#include <print>
#include <random>

export module Night1:TB1ai;
import :Door;
import :Time;

using FGengine::Utils::Timer;

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
			const Timer::DataType timeToEvade = 5;

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
		Timer::DataType attackDelay;
		unsigned attacks = 0;
		Door* door;
		Time* time;
	};

}
