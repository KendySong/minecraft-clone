#ifndef P_TIMER
#define P_TIMER
#include <chrono>
#endif

#pragma once
class Timer
{
private :
	std::chrono::time_point<std::chrono::steady_clock> _start;
	std::chrono::time_point<std::chrono::steady_clock> _end;
	float _elapsedTime;
	bool _isRunning;

public :
	Timer();
	void Start();
	void Stop();
	void Restart();
	float GetElapsedTime();
};