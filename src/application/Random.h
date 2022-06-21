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
	static Random* Instance();
	int FastRand();
	void SetSeed(int seed);
};