#include "BasicRandom.h"

float BasicRandom::Range(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());
	using Dist = std::uniform_real_distribution<float>;
	static Dist dist{};
	return dist(mt, Dist::param_type(min, max));
}

int BasicRandom::Range(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());
	using Dist = std::uniform_int_distribution<int>;
	static Dist dist{};
	return dist(mt, Dist::param_type(min, max));
}
