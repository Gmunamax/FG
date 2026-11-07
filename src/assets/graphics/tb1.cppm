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
#include <span>
#include <FGengine/graphics/model.hpp>

export module Graphics:TB1;
import :BasicShader;

using FGengine::Graphics::Model;

namespace Graphics{

class TB1: public Model{
public:
	TB1():
		Model{GetModel(), GetShader()}
	{}

private:
	static std::span<float> GetModel(){
		static float vertexes[]{
			1, 0, -1,
			-1, 0, 1,
			-1, 0, -1,

			-1, 0, 1,
			1, 0, -1,
			1, 0, 1
		};

		return vertexes;
	}

	static const std::shared_ptr<BasicShader>& GetShader(){
		static BasicShader shader{0.5, 0.5, 0.5};
		static std::shared_ptr<BasicShader> ptr{&shader};

		return ptr;
	}
};

}
