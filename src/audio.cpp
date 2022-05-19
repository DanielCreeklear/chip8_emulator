#include "audio.h"

void Audio::initTimer()
{
    timerRunning = true;
    // BEEP
    timerInit = std::chrono::steady_clock::now();
}

void Audio::resetTimer()
{
    timerInit = std::chrono::steady_clock::now();
}
void Audio::stopTimer()
{
    timerRunning = false;
}

bool Audio::isTimerRunning()
{
    return timerRunning;
}