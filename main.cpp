#include <iostream>
#include <gl/glut.h>
#include "cpu.h"

using namespace std;

void update_display();
void idle();

Cpu cpu;
uint8_t*** pixelBuffer = NULL;
static int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 320;
const int pixelSize = 10;
char fileGame[] = "invaders.c8"; 
char title[] = "CHIP 8 - Emulator";

int main(int argc, char **argv)
{
	pixelBuffer = new uint8_t** [WINDOW_HEIGHT];
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		pixelBuffer[i] = new uint8_t* [WINDOW_WIDTH];
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			pixelBuffer[i][j] = new uint8_t[3];
		}
	}
	cpu.initialize();
	cpu.loadGame(fileGame);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(320, 320);
	glutCreateWindow(title);

	glutDisplayFunc(update_display);
	glutIdleFunc(idle);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glClearColor(0, 0, 0, 0);

	glutMainLoop();
    return 0;
}

void update_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 64; ++x)
		{
			if (y % 2 == 0 && x % 2 == 0)
			{
				glColor3f(1, 1, 1);
			}
			else
			{
				glColor3f(0, 0, 0);
			}

			glBegin(GL_POLYGON);
				glVertex2f((x * pixelSize), WINDOW_HEIGHT - (y * pixelSize));
				glVertex2f(((x + 1) * pixelSize), WINDOW_HEIGHT - (y * pixelSize));
				glVertex2f(((x + 1) * pixelSize), WINDOW_HEIGHT - ((y + 1) * pixelSize));
				glVertex2f((x * pixelSize), WINDOW_HEIGHT - ((y + 1) * pixelSize));
			glEnd();
		}
	}
	glFlush();
	glutSwapBuffers();
}

void idle()
{
	cpu.emulateCycle();
	if (cpu.drawFlag)
	{
		glutPostRedisplay();
		cpu.drawFlag = false;
	}
}