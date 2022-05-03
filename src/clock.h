#pragma once
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace chrono;

class Clock
{
private:
    double REGISTER_PERIOD_MS;

    bool timerRunning;

    steady_clock::time_point timeInitCycle, timerInit;
    int duration;

public:
    Clock();
    ~Clock();
    void initTimer();
    void resetTimer();
    void stopTimer();
    bool isTimerRunning();
    int getTimerRemain();

    void initCycle();
    int getNsCycle();
    bool isCpuClockCompleted();
    int getTimeRemain();
    void init(const float mhz);

    unsigned int CPU_PERIOD_NS;
};