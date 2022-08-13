///Author : kndysong@gmail.com
///Date : 15.04.2022
///Summary : Mesure time for calculate framerate and delta time

#include <chrono>

#pragma once
class Timer
{
	//Attributes and properties
private:
	bool _isRunning;
	std::chrono::time_point<std::chrono::system_clock> _start;
	std::chrono::time_point<std::chrono::system_clock> _stop;
	std::chrono::time_point<std::chrono::system_clock> _elapsed;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	Timer();

	/// <summary>
	/// Start the timer
	/// </summary>
	void Start() noexcept;

	/// <summary>
	/// Restart the timer
	/// </summary>
	void Restart() noexcept;

	/// <summary>
	/// Stop the timer
	/// </summary>
	void Stop() noexcept;

	/// <summary>
	/// Give elapsed time between start and stop
	/// </summary>
	/// <returns>Elapsed time</returns>
	double GetElapsedTime() noexcept;
};