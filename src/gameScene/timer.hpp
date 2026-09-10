#include <chrono>

class Timer{
public:
	using dataType = double;
	using unit = std::ratio<1>;
	using timeType = std::chrono::duration<dataType, unit>;

	dataType GetTime(){
		timeType time = GetCurrentTime() - startTime;
		return time.count();
	}

	void Reset(){
		startTime = GetCurrentTime();
	}

private:
	std::chrono::steady_clock::time_point GetCurrentTime(){
		return std::chrono::steady_clock::now();
	}

	std::chrono::steady_clock::time_point startTime = GetCurrentTime();
};

