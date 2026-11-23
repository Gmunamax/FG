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
#include <FGengine/graphics/properties/objectMatrix.hpp>
#include <FGengine/graphics/properties/objectTransform.hpp>
#include <FGengine/graphics/shader.hpp>

export module Models:Breaker;
import Meshes;
import Shaders;

namespace Models{

	export class Breaker{
	public:
		Breaker(bool state)
		{
			SetActivated(state);
		};

		void Update(const glm::mat4& boardMatrix){
			shader->Use();
			matrix.SetValue(transform.Calculate(boardMatrix));
			matrix.Send();
			mesh.Draw();
		}

		FGengine::Graphics::ObjectTransform& GetTransform(){
			return transform;
		}

		void SetActivated(bool newState){
			activated = newState;
			if(activated){
				color = {0, 1, 0, 0};
			}
			else{
				color = {1, 0, 0, 0};
			}
			color.Send();
		}

		bool GetActivated(bool newState){
			return activated;
		}

	private:
		class TransformInBoard: public FGengine::Graphics::ObjectTransform{
		public:
			glm::mat4 Calculate(const glm::mat4& boardMatrix){
				return boardMatrix * ObjectTransform::Calculate();
			}
		};

		Meshes::Breaker mesh;
		TransformInBoard transform;
		Shaders::Breaker shader;
		FGengine::Graphics::ObjectMatrix matrix{shader->GetHandle()};

		FGengine::Uvec4f color{"color", shader->GetHandle()};

		bool activated;
	};

}
