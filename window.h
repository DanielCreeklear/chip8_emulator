#include <glew.h>
#include <glfw3.h>
#include <iostream>

class Window
{
public:
	Window(int width = 800, int height = 600, const char* title = "");
	void update();
	~Window();

private:
	GLFWwindow *pWindow;
	static void errorCallback(int error, const char* description);
};
