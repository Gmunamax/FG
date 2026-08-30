// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#pragma once
#include "handle.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/structures/vector.hpp"

namespace FGengine{

namespace Backend{

	class Window: protected Handle{
	public:
		using PositionType = Point2i;
		using TitleType = const char*;
		using SizeType = Vector<2, int, VectorType::Size>;
		using MinimumSizeType = Vector<2, int, VectorType::Size>;
		
		Window(TitleType title, SizeType size);
		Window(const Window&) = delete;
		Window(Window&&) = default;
		~Window(){
			Destroy();
		}
		
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&& window){
			if(&window != this){
				Destroy();
				Handle::operator=(std::move(window));
			}
			return *this;
		}

		void Update();

		void SetPosition(PositionType newPosition);
		PositionType GetPosition() const;

		void SetTitle(TitleType newTitle);
		TitleType GetTitle() const;

		void SetSize(SizeType newSize);
		SizeType GetSize() const;

		void SetMinimumSize(MinimumSizeType newMinimumSize);
		MinimumSizeType GetMinimumSize() const;

	private:
		friend struct Internal;
		void Destroy();
	};

}

}
