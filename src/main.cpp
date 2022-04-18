#include <gl/glut.h>
#include "Emulator.h"
#include "Graphics.h"
#include "configs.h"
#include "cpu.h"


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	Cpu *cpu = new Cpu();
	Graphics *graphics = new Graphics(640, 320, &title, cpu, keysMap);

	//Emulator *emulator = new Emulator(640, 320, argv[1]);
	char game[] = "./games/invaders.c8";
	Emulator *emulator = new Emulator(640, 320, game, cpu, keysMap);

    return 0;
}