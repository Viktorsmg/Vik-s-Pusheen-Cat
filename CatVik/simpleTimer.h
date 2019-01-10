#pragma once

#include <chrono>
struct simpleTimer {
	std::chrono::high_resolution_clock::time_point time;
	simpleTimer();
	//Returns amount of time passed since last press in miliseconds
	double press();
};

//OS-independant thread sleep function, works with milliseconds
void sleep_ms(unsigned int ms);