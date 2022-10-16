#pragma once

#include "glad/glad.h"
#include <glfw3.h>
#include <string>

class Window
{
public:
	static GLFWwindow* window;
	static int width;
	static int height;

public:
	static void Init(bool vsync, bool fullscreen, const std::string& name);
	static void Shutdown();
	static bool IsActive();

	static void PollEvents();
	static void SwapBuffers();
};
