#pragma once

#include "glad/glad.h"
#include <glfw3.h>

class Aplication
{
public:
	Aplication();
	~Aplication();

	void Set_GLFW_Callbacks(GLFWkeyfun key_callback, GLFWcursorposfun mouse_callback, GLFWmousebuttonfun mouse_button_callback);
	void Set_ProsessInputs_Function(void (*func)());
	void Set_OnUpdate_Function(void (*func)());
	void Set_Render_Function(void (*func)());
	void Set_RenderGUI_Function(void (*func)());
	void Run();

private:
	void (*ProsessInputs)(void);
	void (*OnUpdate)(void);
	void (*Render)(void);
	void (*RenderGUI)(void);
};
