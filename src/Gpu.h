#pragma once
#include <unordered_map>
#include <iostream>
#include <time.h>
#include <gl/glut.h>
#include "cpu.h"

static std::uint8_t ***pixelBuffer;
static clock_t startTimer;
static int fps = 0;
static Cpu *cpuGraphics;
static std::unordered_map<char, int> *keysMapGraphics;

const int pixelSize = 10;

void buildScreenBuffer(int width, int height);
void update_display();
void idle();
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);

void setCpu(Cpu *cpu);

void setKeysMapGraphics(std::unordered_map<char, int> *keysMapGraphics);

class Gpu
{
private:
	
public:
	Gpu();
	void buildWindow(int width, int height, std::string title);
	void init(int width, int height, std::string *title);
};

