module;
#include <engine/utils/properties/timer.hpp>

export module Night1:Time;

namespace Night1{

	class Time{
	public:
		Time(Timer::dataType endTime):
			endTime{endTime}
		{}

		Timer::dataType GetTime(){
			return timer.GetTime();
		}

		void ResetTimer(){
			timer.Reset();
		}

		Timer::dataType GetEndTime(){
			return endTime;
		}

	private:
		Timer timer;
		Timer::dataType endTime;
	};

}
