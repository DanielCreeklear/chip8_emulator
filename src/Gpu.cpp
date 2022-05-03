#include "Gpu.h"

Gpu::Gpu()
{

}

void Gpu::init(int width, int height, std::string *title)
{
	buildWindow(width, height, *title);
	buildScreenBuffer(width, height);

	startTimer = clock();

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutDisplayFunc(update_display);
	glutIdleFunc(idle);
	gluOrtho2D(0, width, 0, height);
	glClearColor(0, 0, 0, 0);
}

void Gpu::buildWindow(int width, int height, std::string title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(320, 320);
	glutCreateWindow(title.c_str());
}

void setCpu(Cpu *cpu)
{
	cpuGraphics = cpu;
}

void setKeysMapGraphics(std::unordered_map<char, int> *keysMapGraphics)
{
	keysMapGraphics = keysMapGraphics;
}

void buildScreenBuffer(int width, int height)
{
	pixelBuffer = new uint8_t **[height];

	for (int i = 0; i < height; i++)
	{
		pixelBuffer[i] = new uint8_t *[width];
		for (int j = 0; j < width; j++)
		{
			pixelBuffer[i][j] = new uint8_t[3];
		}
	}
}

void idle()
{
	if (fps <= 60)
	{
		cpuGraphics->emulateCycle();

		if (cpuGraphics->drawFlag)
		{
			glutPostRedisplay();

			fps++;


			if ((clock() - startTimer) / CLOCKS_PER_SEC > 1)
			{
				glutSetWindowTitle(((string)(std::to_string(fps) + " FPS")).c_str());
				fps = 0;
				startTimer = clock();
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			cpuGraphics->drawFlag = false;
		}
	}
	else
	{
		fps = 0;
	}
}

void update_display()
{
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 64; ++x)
		{
			if (cpuGraphics->gfx[x + y * 64] & 1)
			{
				glColor3f(1, 1, 1);
			}
			else
			{
				glColor3f(0, 0, 0);
			}

			int x1 = x * pixelSize, x2 = (x + 1) * pixelSize;
			int y1 = y * pixelSize, y2 = (y + 1) * pixelSize;

			glBegin(GL_POLYGON);
				glVertex2f(x1, windowHeight - y1);
				glVertex2f(x2, windowHeight - y1);
				glVertex2f(x2, windowHeight - y2);
				glVertex2f(x1, windowHeight - y2);
			glEnd();
		}
	}

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) 
{
	//cpuGraphics->key[keysMapGraphics[key]] = 1;
	if (key == '1') cpuGraphics->key[1] = 1;
	if (key == '2') cpuGraphics->key[2] = 1;
	if (key == '3') cpuGraphics->key[3] = 1;
	if (key == 'q') cpuGraphics->key[4] = 1;
	if (key == 'w') cpuGraphics->key[5] = 1;
	if (key == 'e') cpuGraphics->key[6] = 1;
	if (key == 'a') cpuGraphics->key[7] = 1;
	if (key == 's') cpuGraphics->key[8] = 1;
	if (key == 'd') cpuGraphics->key[9] = 1;
	if (key == 'z') cpuGraphics->key[10] = 1;
	if (key == 'c') cpuGraphics->key[11] = 1;
	if (key == 'v') cpuGraphics->key[12] = 1;
	if (key == 'f') cpuGraphics->key[13] = 1;
	if (key == 'r') cpuGraphics->key[14] = 1;
	if (key == '4') cpuGraphics->key[15] = 1;
	if (key == 'x') cpuGraphics->key[0] = 1;
}

void keyUp(unsigned char key, int x, int y) 
{
	//cpuGraphics->key[keysMapGraphics[key]] = 0;
	if (key == '1') cpuGraphics->key[1] = 0;
	if (key == '2') cpuGraphics->key[2] = 0;
	if (key == '3') cpuGraphics->key[3] = 0;
	if (key == 'q') cpuGraphics->key[4] = 0;
	if (key == 'w') cpuGraphics->key[5] = 0;
	if (key == 'e') cpuGraphics->key[6] = 0;
	if (key == 'a') cpuGraphics->key[7] = 0;
	if (key == 's') cpuGraphics->key[8] = 0;
	if (key == 'd') cpuGraphics->key[9] = 0;
	if (key == 'z') cpuGraphics->key[10] = 0;
	if (key == 'c') cpuGraphics->key[11] = 0;
	if (key == 'v') cpuGraphics->key[12] = 0;
	if (key == 'f') cpuGraphics->key[13] = 0;
	if (key == 'r') cpuGraphics->key[14] = 0;
	if (key == '4') cpuGraphics->key[15] = 0;
	if (key == 'x') cpuGraphics->key[0] = 0;
}