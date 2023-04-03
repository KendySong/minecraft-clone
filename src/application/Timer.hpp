#include <chrono>

#pragma once
class Timer
{
public:
	Timer();
	void start() noexcept;
	void restart() noexcept;
	void stop() noexcept;
	double getElapsedTime() noexcept;

private:
	bool _isRunning;
	std::chrono::time_point<std::chrono::system_clock> m_start;
	std::chrono::time_point<std::chrono::system_clock> m_stop;
	std::chrono::time_point<std::chrono::system_clock> m_elapsed;
};