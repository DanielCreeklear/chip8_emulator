#include "Emulator.h"

Emulator::Emulator(int width, int height, string *game, std::string* title)
{
	cpu = new Cpu();
	gpu = new Gpu(cpu);

	displayWidth = width;
	displayHeight = height;

	gpu->init(width, height, title);
	
	glutIdleFunc(idle);
	glutReshapeFunc(reshape_window);
	glutDisplayFunc(update_display);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	cpu->initialize(2.0f);
	cpu->loadGame(game);

	glutMainLoop();
}

void Emulator::setkeysMap()
{
	std::vector<Key> keys;

	// Read config.txt
	keys.push_back({'1', 1});
	keys.push_back({'2', 2});
	keys.push_back({'3', 3});
	keys.push_back({'q', 4});
	keys.push_back({'w', 5});
	keys.push_back({'e', 6});
	keys.push_back({'a', 7});
	keys.push_back({'s', 8});
	keys.push_back({'d', 9});
	keys.push_back({'z', 10});
	keys.push_back({'c', 11});
	keys.push_back({'v', 12});
	keys.push_back({'f', 13});
	keys.push_back({'r', 14});
	keys.push_back({'4', 15});
	keys.push_back({'x', 0});;

	//for (Key key : keys) setKeyMap(key);
}

void Emulator::setKeyMap(Key key)
{
	keysMap->insert(pair<char, int> {key.key, key.index});
}

void idle()
{
	timeAux = glutGet(GLUT_ELAPSED_TIME);
	if (timeAux - timebase > 1000)
	{
		fps = frame * 1000.0 / (timeAux - timebase);
		stringstream stream;
		stream << "FPS: " << fps;
		stringFPS = stream.str();
		//std::cout << stringFPS << '\n';
		timebase = timeAux;
		frame = 0;
	}

	cpu->emulateCycle();

	glutPostRedisplay();
	if (cpu->drawFlag)
	{
		//glPushMatrix();
		//glLoadIdentity();
		//renderBitmapString(20, 20, stringFPS);
		//glPopMatrix();
	}
}

void update_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderBitmapString(0, 0, stringFPS);
	if (cpu->drawFlag)
	{
		gpu->refreshScreenBuffer();
		gpu->drawFrame(displayHeight);

		frame++;
		cpu->drawFlag = false;

		glFlush();
		glutSwapBuffers();
	}
}

void reshape_window(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//gluOrtho2D(0, w, 0, h);

	displayWidth = w;
	displayHeight = h;
}

void keyDown(unsigned char key, int x, int y)
{
	//cpu->key[keysMapGraphics[key]] = 1;
	if (key == '1') cpu->key[1] = 1;
	if (key == '2') cpu->key[2] = 1;
	if (key == '3') cpu->key[3] = 1;
	if (key == 'q') cpu->key[4] = 1;
	if (key == 'w') cpu->key[5] = 1;
	if (key == 'e') cpu->key[6] = 1;
	if (key == 'a') cpu->key[7] = 1;
	if (key == 's') cpu->key[8] = 1;
	if (key == 'd') cpu->key[9] = 1;
	if (key == 'z') cpu->key[10] = 1;
	if (key == 'c') cpu->key[11] = 1;
	if (key == 'v') cpu->key[12] = 1;
	if (key == 'f') cpu->key[13] = 1;
	if (key == 'r') cpu->key[14] = 1;
	if (key == '4') cpu->key[15] = 1;
	if (key == 'x') cpu->key[0] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
	//cpu->key[keysMapGraphics[key]] = 0;
	if (key == '1') cpu->key[1] = 0;
	if (key == '2') cpu->key[2] = 0;
	if (key == '3') cpu->key[3] = 0;
	if (key == 'q') cpu->key[4] = 0;
	if (key == 'w') cpu->key[5] = 0;
	if (key == 'e') cpu->key[6] = 0;
	if (key == 'a') cpu->key[7] = 0;
	if (key == 's') cpu->key[8] = 0;
	if (key == 'd') cpu->key[9] = 0;
	if (key == 'z') cpu->key[10] = 0;
	if (key == 'c') cpu->key[11] = 0;
	if (key == 'v') cpu->key[12] = 0;
	if (key == 'f') cpu->key[13] = 0;
	if (key == 'r') cpu->key[14] = 0;
	if (key == '4') cpu->key[15] = 0;
	if (key == 'x') cpu->key[0] = 0;
}

void renderBitmapString(float x, float y, string stringPrint)
{
	glRasterPos2f(x, y);
	glColor3f(1, 1, 1);
	//std::cout << "Printing: " << stringPrint << '\n';
	for (char& c : stringPrint) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}