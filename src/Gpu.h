#pragma once
#include <unordered_map>
#include <time.h>
#include <gl/glut.h>
#include "cpu.h"

/*
std::uint8_t ***pixelBuffer;
clock_t startTimer;
int fps = 0;
*/
static Cpu *cpuGraphics;
static std::unordered_map<char, int> *keysMapGraphics;

const int pixelSize = 10;

//void buildScreenBuffer(int width, int height);
void update_display();
void idle();
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);

class Gpu
{
private:
	void buildWindow(int width, int height, std::string title);

public:
	Gpu(int width, int height, std::string *title, Cpu *cpu, std::unordered_map<char, int> *keysMap);
};

