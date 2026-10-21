module;
#include <FGengine/utils/timer.hpp>

export module Night1:Time;

using FGengine::Utils::Timer;

namespace Night1{

	class Time{
	public:
		Time(Timer::DataType endTime):
			endTime{endTime}
		{}

		Timer::DataType GetTime(){
			return timer.GetTime();
		}

		void ResetTimer(){
			timer.Reset();
		}

		Timer::DataType GetEndTime(){
			return endTime;
		}

	private:
		Timer timer;
		Timer::DataType endTime;
	};

}
