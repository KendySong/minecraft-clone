#include "Random.h"

Random::Random(int seed) 
{
	_seed = seed;
}

int Random::fastrand(int min, int max) 
{
	_seed = (214013 * _seed + 2531011);
	return ((_seed >> 16) & 0x7FFF) % max + min;
}