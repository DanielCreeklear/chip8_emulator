#include "window.h"


Window::Window(int width, int height, const char* title)
{
	needClose = true;

	if (!glfwInit())
	{
		std::cerr << "Error starting GLFW!" << std::endl;
		return;
	}

	// Defining the OpenGL Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);

	glfwSetErrorCallback(Window::errorCallback);

	// Creating Window
	mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!mainWindow)
	{
		std::cerr << "Error building window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(mainWindow);

	// Initializing GLEW
	GLenum glewInitStatus = glewInit();

	if (glewInitStatus != GLEW_OK)
	{
		std::cerr << "Error starting GLEW: " << glewGetErrorString(glewInitStatus) << std::endl;
		return;
	}

	// Show status environment
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	std::cout << "Render: " << renderer << std::endl;
	std::cout << "Version support opengl: " << version << std::endl;

	glClearColor(0, 0, 0, 0);

	needClose = false;
}

void Window::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();

	if (currentScene) currentScene->update();

	glfwSwapBuffers(mainWindow);

	if (!needClose) needClose = (glfwWindowShouldClose(mainWindow) == GL_TRUE);
}

Window::~Window()
{

}

void Window::errorCallback(int error, const char *description)
{
	std::cerr << "Error[" << error << "]: " << description << std::endl;
}