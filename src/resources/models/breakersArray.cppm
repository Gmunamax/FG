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
#include <FGengine/graphics/properties/objectTransform.hpp>
#include <memory>

export module Models:BreakersArray;
import :Breaker;

using FGengine::Graphics::ObjectTransform;

namespace Models{

	export class BreakersArray{
	public:
		BreakersArray(std::array<bool, 10> breakersStates){
			for(std::size_t i = 0; i < 10; ++i){
				this->breakers.at(i).SetActivated(breakersStates.at(i));
			}
			FillWithModels({0,0,0}, 5, 2, 0.3, 0.8, breakers);
		}

		void Update(){
			transformMatrix = transform.Calculate();
			for(auto& breaker : breakers){
				breaker.Update(transformMatrix);
			}
		}

		ObjectTransform& GetTransform(){
			return transform;
		}

		void SetActivated(unsigned breaker, bool newState){
			breakers.at(breaker).SetActivated(newState);
		}

	private:
		class DefaultedModel: public Models::Breaker{
		public:
			DefaultedModel():
				Models::Breaker(true)
			{}

		};

		static void FillWithModels(glm::vec3 center, std::size_t width, std::size_t height, float xStep, float yStep, std::span<DefaultedModel> models){
			float xCenter = (xStep*(width-1))/2;
			float yCenter = (yStep*(height-1))/2;
			center -= glm::vec3{xCenter, 0, yCenter};
			for(std::size_t i = 0; i < height; ++i){
				for(std::size_t j = 0; j < width; ++j){
					auto& breaker = models.at(5*i+j);
					breaker.GetTransform().SetPosition(center + glm::vec3{xStep*j, 0, yStep*i});
				}
			}
		}

		std::array<DefaultedModel, 10> breakers;
		ObjectTransform transform;
		glm::mat4 transformMatrix{1};
	};

}
