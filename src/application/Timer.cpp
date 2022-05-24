#include "Timer.h"

Timer::Timer() 
{
	_elapsedTime = 0;
	_isRunning = false;
}

void Timer::Start() 
{
	_isRunning = true;
	_start = std::chrono::steady_clock::now();
}

void Timer::Stop() 
{
	if (_isRunning)
	{
		_isRunning = false;
		_end = std::chrono::steady_clock::now();
	}
}

void Timer::Restart()
{
	this->Start();
}

float Timer::GetElapsedTime() 
{
	_end = std::chrono::steady_clock::now();
	_elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
	return _elapsedTime;
}