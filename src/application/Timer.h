#ifndef P_TIMER
#define P_TIMER
#include <chrono>
#endif

class Timer
{
private:
	bool _isRunning;
	std::chrono::time_point<std::chrono::system_clock> _start;
	std::chrono::time_point<std::chrono::system_clock> _stop;
	std::chrono::time_point<std::chrono::system_clock> _elapsed;

public:
	Timer();
	void Start();
	void Restart();
	void Stop();
	double GetElapsedTime();
};