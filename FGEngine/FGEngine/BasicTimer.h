#pragma once


struct BasicTimer
{
	BasicTimer() = default;
	BasicTimer(float timer) : timer(timer), accu(0.0f) {}

	void Update(float dt)
	{
		accu += dt;
	}

	bool IsReady()
	{
		return accu >= timer;
	}

	void Use()
	{
		accu = 0;
	}

private:
	float accu;
	float timer;
};