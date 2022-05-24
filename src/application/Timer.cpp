#include "Timer.h"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	_start = std::chrono::system_clock::now();
	_isRunning = true;
}

void Timer::Restart()
{
	Start();
}

void Timer::Stop()
{
	_stop = std::chrono::system_clock::now();
	_isRunning = false;
}

double Timer::GetElapsedTime()
{
	if (_isRunning)
		_elapsed = std::chrono::system_clock::now();
	else
		_elapsed = _stop;

	return std::chrono::duration_cast<std::chrono::microseconds>(_elapsed - _start).count() * 0.000001;
}