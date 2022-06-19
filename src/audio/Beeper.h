#include <string>
#include <memory>
#include <stdio.h>
#include <SDL.h>

#define MUS_PATH "bleep.wav"

class Beeper
{
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;

public:
	Beeper(const std::string &path, int volume);
	~Beeper();

	void play();
	void stop();
};

