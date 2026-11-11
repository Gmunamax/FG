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
#include <FGengine/graphics/model.hpp>
#include <FGengine/graphics/shader.hpp>
#include <span>
#include <vector>

export module Models:Office;
import :BasicShader;

using FGengine::Graphics::Model;

namespace Models{

class Office: public Model{
public:
	Office():
		Model{officeVertexes, GetShader()}
	{}

private:
	static std::span<float> GetVertexes();
	static std::span<unsigned> GetIndices();
	static std::vector<float> officeVertexes;

	static std::shared_ptr<BasicShader> GetShader(){
		static BasicShader shader{1, 0, 0};
		static std::shared_ptr<BasicShader> ptr{&shader};
		return ptr;
	}
};

}
