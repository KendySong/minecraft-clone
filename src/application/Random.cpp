#include "Random.h"

Random* Random::_random = nullptr;

Random::Random() 
{
	_seed = -1;
	_isSeedSet = false;
}

Random* Random::Instance() 
{
	if (_random == nullptr)
		_random = new Random();
	return _random;
}

int Random::FastRand() 
{
	if (_seed == -1 || !_isSeedSet)
	{
		_seed = time(nullptr);
		_isSeedSet = true;
	}

	_seed = (214013 * _seed + 2531011);
	return (_seed >> 16) & 0x7FFF;
}

void Random::SetSeed(int seed) 
{
	_seed = seed;
	_isSeedSet = true;
}