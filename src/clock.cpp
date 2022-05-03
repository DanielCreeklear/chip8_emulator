#include "clock.h"

Clock::Clock()
{

}

Clock::~Clock()
{

}

void Clock::init(const float mhz)
{
    CPU_PERIOD_NS = pow(10, 9) / (mhz * pow(10, 6));
    REGISTER_PERIOD_MS = 1 / (60 * pow(10, 3));
}

void Clock::initTimer()
{
    timerRunning = true;
    timerInit = std::chrono::steady_clock::now();
}

void Clock::resetTimer()
{
    timerInit = std::chrono::steady_clock::now();
}
void Clock::stopTimer()
{
    timerRunning = false;
}

bool Clock::isTimerRunning()
{
    return timerRunning;
}

int Clock::getTimerRemain()
{
    int diff = duration_cast<milliseconds> (steady_clock::now() - timerInit).count();

    if (diff > 16)
    {
        return 0;
    }
    else
    {
        return 16 - diff;
    }
}

void Clock::initCycle()
{
    timeInitCycle = std::chrono::steady_clock::now();
}

int Clock::getNsCycle()
{
    int aux = duration_cast<nanoseconds> (steady_clock::now() - timeInitCycle).count();
    if (aux < 0)
    {
        return 0;
    }
    else
    {
        return aux;
    }
}

bool Clock::isCpuClockCompleted()
{
    return getNsCycle() > CPU_PERIOD_NS;
}

int Clock::getTimeRemain()
{
    unsigned int period = getNsCycle();
    if (period > CPU_PERIOD_NS)
    {
        return 0;
    }
    else
    {
        return CPU_PERIOD_NS - period;
    }
}