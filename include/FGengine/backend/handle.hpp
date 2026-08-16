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

namespace FGengine{

namespace Backend{

	class Handle{
	private:
		void* handle;

	public:
		void* GetHandle() const{
			return handle;
		}

	protected:
		void SetHandle(void* newHandle){
			handle = newHandle;
		}

		Handle(void* handle): handle(handle) {}
		Handle(const Handle&) = delete;
		Handle(Handle&& handle): handle(handle.handle){
			handle.handle = nullptr;
		}
		~Handle() = default;

		Handle& operator=(const Handle&) = delete;
		Handle& operator=(Handle&& handle){
			if(&handle != this){
				this->handle = handle.handle;
				handle.handle = nullptr;
			}
			return *this;
		}
	};

}

}
