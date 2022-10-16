#include "Window.h"

#include <iostream>

GLFWwindow* Window::window;
int Window::width;
int Window::height;

void Window::Init(bool vsync, bool fullscreen, const std::string& name)
{
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	width = mode->width;
	height = mode->height;

	if (fullscreen)
	{
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		
		window = glfwCreateWindow(mode->width, mode->height, name.c_str(), primary, NULL);
	}
	else
	{
		window = glfwCreateWindow(mode->width / 2, mode->height / 2, name.c_str(), NULL, NULL);
	}

	if (!window) 
	{
		glfwTerminate();
	}
	else
	{
		glfwMakeContextCurrent(window);
		glfwSwapInterval(vsync);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		std::cout << ("gladLoadGLLoader() Failed");
	}
}

void Window::Shutdown()
{
	glfwTerminate();
}

bool Window::IsActive()
{
	return !glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}
