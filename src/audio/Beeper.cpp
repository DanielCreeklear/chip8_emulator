#include "Beeper.h"

Beeper::Beeper(const std::string& path, int volume)
{
	SDL_LoadWAV(path.c_str(), &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

Beeper::~Beeper()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();
}

void Beeper::play()
{
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, false);
}

void Beeper::stop()
{
	SDL_PauseAudioDevice(deviceId, true);
}