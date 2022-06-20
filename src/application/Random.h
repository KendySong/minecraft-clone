///Author : Kendy Song
///Date : 20.06.2022
///Summary : Generate random number

#pragma once
class Random 
{
private :
	int _seed;

public :
	Random(int seed);

	int fastrand(int min, int max);
};