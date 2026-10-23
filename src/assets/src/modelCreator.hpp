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
#pragma once
#include <vector>
#include <span>

inline std::vector<float> ConvertToVertexArray(const std::span<float> vertexes, const std::span<unsigned> indices){
	constexpr unsigned vertexLength = 3;
	std::vector<float> vertexArray;

	for(auto index : indices){
		index = (index-1)*3;
		for(unsigned int i = 0; i < vertexLength; ++i){
			vertexArray.push_back(vertexes[index+i]);
		}
	}

	return vertexArray;
}
