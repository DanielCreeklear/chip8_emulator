#include "clock.h"

Clock::Clock()
{

}

Clock::~Clock()
{

}

void Clock::init(const float mhz)
{
    CPU_PERIOD_MS = 1 / (mhz * pow(10, 3));
    REGISTER_PERIOD_MS = 1 / (60 * pow(10, 3));
    timeLastCycle = std::chrono::steady_clock::now();
    timeLastRegister = std::chrono::steady_clock::now();
}

bool Clock::getCpuClock()
{
    if (std::chrono::duration_cast <std::chrono::milliseconds> (std::chrono::steady_clock::now() - timeLastCycle).count() > CPU_PERIOD_MS)
    {
        timeLastCycle = std::chrono::steady_clock::now();
        return true;
    }
    else
    {
        return false;
    }
}

bool Clock::getRegisterClock()
{
    if (std::chrono::duration_cast <std::chrono::milliseconds> (std::chrono::steady_clock::now() - timeLastCycle).count() > REGISTER_PERIOD_MS)
    {
        timeLastRegister = std::chrono::steady_clock::now();
        return true;
    }
    else
    {
        return false;
    }
}