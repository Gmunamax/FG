#pragma once
#include <vector>
#include "windowBase.hpp"



class Window: public WindowBase{

	static inline std::vector<Window*> allwindows;
	std::vector<Window*>::size_type vectorpos;

	void AddSelf();

	void RemoveSelf();

public:

	Window();
	~Window();

	static void CloseAll();

	void Load();

	static void SendEvent();
	static void DrawAll();
};