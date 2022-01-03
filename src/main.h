#pragma once
#include <iostream>
#include <time.h>
#include <gl/glut.h>
#include "cpu.h"

using namespace std;

void update_display();
void idle();
void keyUp(unsigned char key, int x, int y);
void keyDown(unsigned char key, int x, int y);

Cpu cpu;
uint8_t*** pixelBuffer = NULL;
static int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 320;
const int pixelSize = 10;
char title[] = "CHIP 8 - Emulator";

int fps = 0;
clock_t startTimer;