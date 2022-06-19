#include "audio.h"

Audio::Audio()
{
    timerRunning = false;
    duration = 1000;
    Hz = 440;
    std::string wavBeep = "bleep.wav";
    beeper = new Beeper(wavBeep, 10);
}

Audio::~Audio()
{

}

void Audio::play()
{
    if (isTimerRunning())
    {
        if (isTimerFinished())
        {
            stopTimer();
            stopBeep();
        }
    }
    else
    {
        initTimer();
        beep();
    }
}

void Audio::beep()
{
    beeper->play();
}

void Audio::stopBeep()
{
    beeper->stop();
}

void Audio::initTimer()
{
    timerRunning = true;
    timerInit = std::chrono::steady_clock::now();
}

void Audio::stopTimer()
{
    if (isTimerRunning()) timerRunning = false;
}

bool Audio::isTimerRunning()
{
    return timerRunning;
}

bool Audio::isTimerFinished()
{
    int diff = duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - timerInit).count();
    if (diff > 16.6)
    {
        return true;
    }
    else
    {
        return false;
    }
}