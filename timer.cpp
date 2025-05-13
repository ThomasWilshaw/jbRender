#include "timer.h"

Timer::Timer(std::string name)
{
	name_ = name;
	start_ = high_resolution_clock::now();
}

Timer::~Timer()
{
	stop_ = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop_ - start_);

	double d = duration.count() / 1000000.0;

	std::cout << name_ << ": "  << d << " seconds" << std::endl;
}