#pragma once

struct EventsPack{
	enum class Key{
		W,A,S,D,
		Up,Left,Down,Right,
		Space,
		Lshift, Rshift,
		B
	};

	virtual void Draw() = 0;
	virtual void KeyPress(Key key) = 0;
	virtual void KeyRelease(Key key) = 0;
};
