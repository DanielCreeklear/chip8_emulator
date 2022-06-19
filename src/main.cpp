#include <gl/glut.h>
#include <iostream>
#include "emulator/Emulator.h"
#include "configs.h"
#include "cpu/cpu.h"


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	std::cout << "OpenGL initialized" << std::endl;
	if (SDL_Init(SDL_INIT_AUDIO))
		return 1;
	string gamePath;

	if (argc <= 1)
	{
		std::cout << "Enter the path with the file to read: ";
		std::cin >> gamePath;
	}
	else
	{
		gamePath = argv[1];
	}

	Emulator *emulator = new Emulator(640, 320, &gamePath, &title);

    return 0;
}