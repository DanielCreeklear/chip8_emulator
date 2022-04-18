#pragma once
#include <unordered_map>
#include <gl/glut.h>
#include "cpu.h"

struct Key
{
	unsigned char key;
	int index;
};


class Emulator
{
private:
	std::unordered_map<char, int> *keysMapEmulator;
	Cpu *cpu;

	void setkeysMapEmulator();
	void setKeyMap(Key key);

public:
	Emulator(int width, int height, char *game, Cpu *cpu, std::unordered_map<char, int> *keysMap);
};