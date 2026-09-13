#pragma once
#include <engine/utils/properties/timer.hpp>
#include <engine/utils/properties/movement.hpp>
#include <glm/vec3.hpp>

class Player{
public:
	using TimeType = float;

	void Update(){
		TimeType time = drawTimer.GetTime();
		drawTimer.Reset();

		UpdateProperties(time);
	}

protected:
	virtual void UpdateProperties(TimeType time) = 0;
	
private:
	Timer drawTimer;
};
