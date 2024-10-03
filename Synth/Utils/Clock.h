#pragma once
#include <chrono>

class Clock
{
public:
	static uint64_t GetTime();
	static uint64_t Zero();
};

