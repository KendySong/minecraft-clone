#include "Random.hpp"

Random* Random::p_random = nullptr;

Random::Random() 
{
	m_seed = -1;
	m_isSeedSet = false;
}

Random* Random::instance() 
{
	if (p_random == nullptr)
		p_random = new Random();
	return p_random;
}

int Random::fastRand() 
{
	if (m_seed == -1 || !m_isSeedSet)
	{
		m_seed = time(nullptr);
		m_isSeedSet = true;
	}

	m_seed = (214013 * m_seed + 2531011);
	return (m_seed >> 16) & 0x7FFF;
}

void Random::setSeed(int seed) 
{
	m_seed = seed;
	m_isSeedSet = true;
}