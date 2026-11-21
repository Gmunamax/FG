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
#include <array>
#include <span>
#include <glm/vec3.hpp>

export module Graphics:BreakersBoard;
import Models;

namespace Graphics{

	class BreakersSet{
	public:
		BreakersSet(std::array<bool, 10> breakersStates){
			for(std::size_t i = 0; i < 10; ++i){
				this->breakers.at(i) = Models::Breaker{breakersStates.at(i)};
			}
		}

		void SetPosition(const glm::vec3& newPosition){
			FillWithModels(newPosition, 5, 2, 0.3, 0.8, breakers);
		}

		void Draw(){
			for(auto& breaker : breakers){
				breaker.Draw();
			}
		}

		void SetActivated(unsigned breaker, bool newState){
			breakers.at(breaker).SetActivated(newState);
		}

	private:
		class Model: public Models::Breaker{
		public:
			Model():
				Models::Breaker(true)
			{}

			Model(Models::Breaker model):
				Models::Breaker(std::move(model))
			{}
		};

		static void FillWithModels(glm::vec3 center, std::size_t width, std::size_t height, float xStep, float yStep, std::span<Model> models){
			float xCenter = (xStep*(width-1))/2;
			float yCenter = (yStep*(height-1))/2;
			center -= glm::vec3{xCenter, 0, yCenter};
			for(std::size_t i = 0; i < height; ++i){
				for(std::size_t j = 0; j < width; ++j){
					auto& breaker = models.at(5*i+j);
					breaker.SetPosition(center + glm::vec3{xStep*j, 0, yStep*i});
				}
			}
		}

		std::array<Model, 10> breakers;
	};

	export class BreakersBoard{
	public:
		BreakersBoard(std::array<bool, 10> breakersStates):
			breakers{breakersStates}
		{
			breakers.SetPosition({0, 5, 0});
		}

		void Draw(){
			breakers.Draw();
		}

		void SetActivated(unsigned breaker, bool newState){
			breakers.SetActivated(breaker, newState);
		}

	private:
		BreakersSet breakers;
	};

}
