#include "Clock.h"

uint64_t Clock::GetTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t Clock::Zero()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds::zero()).count();
}
