///Author : Kendy Song
///Date : 20.06.2022
///Summary : Generate random number

#include <chrono>

#pragma once
class Random
{
private :
	
	int _seed;
	bool _isSeedSet;

	static Random* _random;
	Random();

public :

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static Random* Instance();

	/// <summary>
	/// Generate random number
	/// </summary>
	/// <returns>Random number</returns>
	int FastRand();

	/// <summary>
	/// Set seed
	/// </summary>
	/// <param name="seed">Seed to set</param>
	void SetSeed(int seed);
};