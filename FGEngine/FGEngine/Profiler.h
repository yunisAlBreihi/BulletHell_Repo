#pragma once
#include <chrono>
#include <string>
#include <iostream>


class Profiler
{
public:
	using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
	using Time = std::chrono::high_resolution_clock;
	using DurationCast = decltype(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::nanoseconds()));

	void Start(std::string name, bool report = false)
	{
		_report = report;
		this->name = name;
		begin = Time::now();
	}

	float End()
	{
		end = Time::now();
		auto delta = end - begin;
		auto ms = DurationCast(delta).count() * 0.000000001f;
		begin = end;

		if (_report)
		{
			//std::cout << name << ms << std::endl;
		}
		return ms;
	}

	std::string name;
	TimePoint begin;
	TimePoint end;
	bool _report;
};