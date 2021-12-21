#pragma once
#include <chrono>

class Clock
{
private:
    double REGISTER_PERIOD_MS;
    double CPU_PERIOD_MS;
    std::chrono::steady_clock::time_point timeLastCycle, timeLastRegister;
public:
    Clock();
    ~Clock();
    bool getCpuClock();
    bool getRegisterClock();
    void init(const float mhz);
};