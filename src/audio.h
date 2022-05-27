#pragma once
#include <chrono>
#include <string>
#include <iostream>
#include "Beeper.h"


class Audio
{
private:
	bool timerRunning;
	int duration;
	double Hz;
	std::chrono::steady_clock::time_point timeInitCycle, timerInit;
	Beeper* beeper;

public:
	Audio();
	~Audio();

	void beep();
	void stopBeep();

	void play();
	void initTimer();
	void stopTimer();
	bool isTimerRunning();
	bool isTimerFinished();
};

