#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <memory>
#include "scene.h"

class Window
{
public:
	Window(int width = 800, int height = 600, const char* title = "");
	~Window();
	
	void update();

	inline bool shouldClose() const { return needClose; }
	inline void setScene(std::unique_ptr<Scene> scene) { currentScene = std::move(scene); }

private:
	GLFWwindow *mainWindow;
	bool needClose;
	std::unique_ptr<Scene> currentScene = nullptr;
	static void errorCallback(int error, const char* description);
};
