#include "Timer.hpp"

Timer::Timer()
{
	start();
}

void Timer::start() noexcept
{
	m_start = std::chrono::system_clock::now();
	_isRunning = true;
}

void Timer::restart() noexcept
{
	start();
}

void Timer::stop() noexcept
{
	m_stop = std::chrono::system_clock::now();
	_isRunning = false;
}

double Timer::getElapsedTime() noexcept
{
	if (_isRunning)
		m_elapsed = std::chrono::system_clock::now();
	else
		m_elapsed = m_stop;

	return std::chrono::duration_cast<std::chrono::microseconds>(m_elapsed - m_start).count() * 0.000001;
}