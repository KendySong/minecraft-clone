#include <chrono>

#pragma once
class Random
{
private :
	Random();

public:
	static Random* instance();
	int fastRand();
	void setSeed(int seed);

private :
	int m_seed;
	bool m_isSeedSet;
	static Random* p_random;
};