#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
using namespace std::chrono;

class Timer
{
public:
	Timer(std::string name);

	~Timer();

private:
	steady_clock::time_point start_;
	steady_clock::time_point stop_;
	std::string name_;
};



#endif // TIMER_H