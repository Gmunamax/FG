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
#include <chrono>
#include "FGengine/special/scene.hpp"
#include "FGengine/special/defaults.hpp"
#include "FGengine/structures/frametime.hpp"
#include "FGengine/special/framebuffer.hpp"
#include "FGengine/backend/window.hpp"

namespace FGengine{

class Window: public Backend::Window, public Framebuffer{
//flags

private:
	using FlagFieldType = Uint8;
	FlagFieldType flagsfield = 0;
	enum class Flags{
		MinSize    = 0b00000001,
		Vsync      = 0b00000010,
		Size       = 0b00000100,
		Title      = 0b00001000,
		Position   = 0b00010000,
		Drawing    = 0b00100000,
	};

	void SetFlags(Flags flags){
		flagsfield |= (FlagFieldType)flags;
	}
	void RemoveFlags(Flags flags){
		flagsfield &= ~(FlagFieldType)flags;
	}
	void InverseFlags(Flags flags){
		flagsfield &= (FlagFieldType)flags;
	}
	FlagFieldType GetFlags(Flags flags){
		return flagsfield & (FlagFieldType)flags;
	}

//flags


//drawing
public:
	enum class FramerateLimitType{
		Delay,
		Check,
	};

private:
	Frametime frametimelimit {0};
	FramerateLimitType limittype{FramerateLimitType::Delay};
	std::chrono::steady_clock::time_point t1, t2;

	Frametime realframetime;

	void RenderScene();
	
	void ProceedUpdate();
	void UpdateByDelayLimit();
	void UpdateByCheckLimit();
	void UpdateByNoneLimit();

public:	
	void SetFrametimeLimit(const Frametime& ms);
	const Frametime& GetFrametimeLimit();
	void SetFramerateLimitType(const FramerateLimitType& limittype);
	const FramerateLimitType& GetFramerateLimitType();

	void RequestNewFrame();

//drawing


//events

private:
	Scene* scene {Defaults::scene};

	static Window* GetWindowFromID(const Uint32& id);

	static void SendEvents();

	void BindWindowToScene();
	
public:
	Scene* const& GetScene();
	void SetScene(Scene* const& newscene);

//events


//cycle

private:
	static inline std::forward_list<Window*> allwindows;
	std::forward_list<Window*>::iterator elementBeforeThisInList;

public:
	static void CycleAll();
	void Cycle();

//cycle

void UseFramebuffer();

//main

private:
	bool opened = false;

public:
	void Select();

	void Open();
	void Close();

	static void CloseAll();

	Window(TitleType title, SizeType size);
	~Window();

//main
};

}
