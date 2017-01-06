#include "TimeCounter.h"


void TimeCounter::start_timer()
{
	start = std::chrono::system_clock::now();
	started = true;
}

void TimeCounter::stop_timer()
{
	if(started)
		end = std::chrono::system_clock::now();
}

double TimeCounter::getTime()
{
	std::chrono::duration<double> elapsed_time = end-start; return elapsed_time.count();
}