#include "simpleTimer.h"

#include <thread>

simpleTimer::simpleTimer() { time = std::chrono::high_resolution_clock::now(); }
//Returns amount of time passed since last press in miliseconds
double simpleTimer::press() {
	unsigned int res = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - time).count();
	time = std::chrono::high_resolution_clock::now();
	return res / 1000000.0;
}

void sleep_ms(unsigned int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}