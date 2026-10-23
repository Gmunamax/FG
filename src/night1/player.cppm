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
#include <FGengine/graphics/camera.hpp>

export module Night1:Player;

using FGengine::Graphics::Camera;

namespace Night1{

	class Player{
	public:
		void Update(){
			camera.Update();
		}

		void SetPosition(const glm::vec3& newPosition){
			camera.SetPosition(newPosition);
		}

		glm::vec3 GetPosition(){
			return camera.GetPosition();
		}

		void SetRotation(const glm::vec3& newRotation){
			camera.SetRotation(newRotation);
		}

		glm::vec3 GetRotation(){
			return camera.GetRotation();
		}

	private:
		Camera camera;
	};

}
