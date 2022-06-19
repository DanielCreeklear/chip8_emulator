#pragma once
#include <unordered_map>
#include <gl/glut.h>
#include <string>
#include <iostream>
#include "../cpu/cpu.h"


static std::unordered_map<char, int> *keysMapGraphics;

static int pixelSize = 10;
static int screenBuffer[32][64];

typedef struct
{
	int x;
	int y;
} Vertex;

typedef struct
{
	Vertex vertexA;
	Vertex vertexB;
	bool color;
} Pixel;

class Gpu
{
private:
	Cpu* cpu = NULL;

	Pixel getPixel(int x, int y);
public:
	Gpu(Cpu* cpu);
	void buildWindow(int width, int height, std::string title);
	void init(int width, int height, std::string *title);
	void refreshScreenBuffer();
	void drawFrame(int windowHeight);
};

