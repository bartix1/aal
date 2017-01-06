#pragma once

#include <chrono>


class TimeCounter
{
public:
	void start_timer();
	void stop_timer();
	double getTime();
private:
	std::chrono::time_point<std::chrono::system_clock> start, end;	
	bool started = false;
};