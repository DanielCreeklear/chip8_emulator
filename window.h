#include <glew.h>
#include <glfw3.h>
#include <iostream>

class Window
{
public:
	Window(int width = 800, int height = 600, const char* title = "");
	~Window();
	
	void update();

	inline bool shouldClose() const { return shouldTerminate; }

private:
	GLFWwindow *pWindow;
	bool shouldTerminate;
	static void errorCallback(int error, const char* description);
};
