
#pragma once
class Random 
{
private :
	int _seed;

public :
	Random(int seed);

	int fastrand(int min, int max);
};