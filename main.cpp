#include <iostream>
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
	cpu.initialize(2.0f);
	cpu.loadGame(fileGame);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(320, 320);
	glutCreateWindow(title);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
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
			if (cpu.gfx[x + y * 64] == 1)
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

void keyDown(unsigned char key, int x, int y) {
	if (key == '1') cpu.key[1] = 1;
	if (key == '2') cpu.key[2] = 1;
	if (key == '3') cpu.key[3] = 1;
	if (key == 'q') cpu.key[4] = 1;
	if (key == 'w') cpu.key[5] = 1;
	if (key == 'e') cpu.key[6] = 1;
	if (key == 'a') cpu.key[7] = 1;
	if (key == 's') cpu.key[8] = 1;
	if (key == 'd') cpu.key[9] = 1;
	if (key == 'z') cpu.key[10] = 1;
	if (key == 'c') cpu.key[11] = 1;
	if (key == 'v') cpu.key[12] = 1;
	if (key == 'f') cpu.key[13] = 1;
	if (key == 'r') cpu.key[14] = 1;
	if (key == '4') cpu.key[15] = 1;
	if (key == 'x') cpu.key[0] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	if (key == '1') cpu.key[1] = 0;
	if (key == '2') cpu.key[2] = 0;
	if (key == '3') cpu.key[3] = 0;
	if (key == 'q') cpu.key[4] = 0;
	if (key == 'w') cpu.key[5] = 0;
	if (key == 'e') cpu.key[6] = 0;
	if (key == 'a') cpu.key[7] = 0;
	if (key == 's') cpu.key[8] = 0;
	if (key == 'd') cpu.key[9] = 0;
	if (key == 'z') cpu.key[10] = 0;
	if (key == 'c') cpu.key[11] = 0;
	if (key == 'v') cpu.key[12] = 0;
	if (key == 'f') cpu.key[13] = 0;
	if (key == 'r') cpu.key[14] = 0;
	if (key == '4') cpu.key[15] = 0;
	if (key == 'x') cpu.key[0] = 0;
}