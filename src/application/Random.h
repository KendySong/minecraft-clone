///Author : Kendy Song
///Date : 20.06.2022
///Summary : Generate random number

#include <chrono>

#pragma once
class Random
{
private :
	static Random* _random;

	int _seed;
	bool _isSeedSet;

	/// <summary>
	/// Constructor
	/// </summary>
	Random();

public :

	/// <summary>
	/// Getter of instance of the class
	/// </summary>
	/// <returns>Pointer to the instance</returns>
	static Random* GetInstance();

	/// <summary>
	/// Generate random number
	/// </summary>
	/// <returns>Random number</returns>
	int FastRand() noexcept;

	/// <summary>
	/// Set seed
	/// </summary>
	/// <param name="seed">Seed to set</param>
	void SetSeed(int seed) noexcept;
};