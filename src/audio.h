#pragma once
#include <chrono>


class Audio
{
private:
	bool timerRunning;
	int duration;
	std::chrono::steady_clock::time_point timeInitCycle, timerInit;

public:
	Audio();
	~Audio();

	void initTimer();
	void resetTimer();
	void stopTimer();
	bool isTimerRunning();
	int getTimerRemain();
};

