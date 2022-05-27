#include <gl/glut.h>
#include <iostream>
#include "Emulator.h"
#include "configs.h"
#include "cpu.h"



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	std::cout << "OpenGL initialized" << std::endl;
	if (SDL_Init(SDL_INIT_AUDIO))
		return 1;

	Cpu *cpu = new Cpu();

	//Emulator *emulator = new Emulator(640, 320, argv[1]);
	char game[] = "./games/invaders.c8";
	Emulator *emulator = new Emulator(640, 320, game, &title, cpu, &keysMap);

    return 0;
}