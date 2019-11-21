#pragma once
class BasicRandom
{
public:
	///Range returns a random number between min(inclusive) and max(inclusive)
	//if using for array indices, do max-1 or tell me
	static float Range(float min, float max);
	static int Range(int min, int max);
};
