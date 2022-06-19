#include "Gpu.h"

Gpu::Gpu(Cpu *cpu)
{
	this->cpu = cpu;
}

void Gpu::init(int width, int height, std::string *title)
{
	buildWindow(width, height + 15, *title);
	gluOrtho2D(0, width, 0, height + 15);
	glClearColor(0, 0, 0, 0);
}

void Gpu::buildWindow(int width, int height, std::string title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(320, 320);
	glutCreateWindow(title.c_str());
}

void Gpu::refreshScreenBuffer()
{
	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 64; ++x)
		{
			if (cpu->gfx[x + y * 64])
			{
				screenBuffer[y][x] = 1;
			}
			else
			{
				screenBuffer[y][x] = 0;
			}
		}
	}
}

Pixel Gpu::getPixel(int x, int y)
{
	Pixel pixel;

	pixel.vertexA.x = x * pixelSize;
	pixel.vertexA.y = y * pixelSize;
	pixel.vertexB.x = (x + 1) * pixelSize;
	pixel.vertexB.y = (y + 1) * pixelSize;
	pixel.color = screenBuffer[y][x];

	return pixel;
}

void Gpu::drawFrame(int windowHeight)
{
	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 64; ++x)
		{
			Pixel pixel = getPixel(x, y);

			if (pixel.color)
			{
				glColor3f(1, 1, 1);
			}
			else
			{
				glColor3f(0, 0, 0);
			}

			glBegin(GL_POLYGON);
				glVertex2f(pixel.vertexA.x, windowHeight - pixel.vertexA.y);
				glVertex2f(pixel.vertexB.x, windowHeight - pixel.vertexA.y);
				glVertex2f(pixel.vertexB.x, windowHeight - pixel.vertexB.y);
				glVertex2f(pixel.vertexA.x, windowHeight - pixel.vertexB.y);
			glEnd();
		}
	}

}