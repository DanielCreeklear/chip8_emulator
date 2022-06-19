#pragma once
#include <unordered_map>
#include <sstream>
#include <gl/glut.h>
#include "cpu.h"
#include "Gpu.h"

static Cpu* cpu = NULL;
static Gpu* gpu = NULL;

static int fps = 0;
static int frame = 0;
static int timeAux;
static int timebase = 0;
static string stringFPS;
static int displayWidth = 0;
static int displayHeight = 0;

void idle();
void update_display();
void reshape_window(GLsizei w, GLsizei h);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void renderBitmapString(float x, float y, string stringPrint);

struct Key
{
	unsigned char key;
	int index;
};

class Emulator
{
private:
	std::unordered_map<char, int> *keysMap;
	

	void setkeysMap();
	void setKeyMap(Key key);

public:
	Emulator(int width, int height, string *game, std::string *title);
};