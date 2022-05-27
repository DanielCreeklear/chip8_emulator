#pragma once
#include <unordered_map>
#include "cpu.h"
#include "Gpu.h"

struct Key
{
	unsigned char key;
	int index;
};


class Emulator : public Gpu
{
private:
	std::unordered_map<char, int> *keysMap;
	Cpu *cpu;

	void setkeysMap();
	void setKeyMap(Key key);

public:
	Emulator(int width, int height, string *game, std::string *title, Cpu *cpu);
};