#include "Application.h"

#include "Renderer.h"
#include "Window.h"
#include "GUI.h"
#include "Camera.h"
#include "Time.h"
#include "Log.h"

using rendering::Renderer;
using rendering::Camera;

Aplication::Aplication()
{
    ProsessInputs = NULL;
    OnUpdate = NULL;
    Render = NULL;
    RenderGUI = NULL;

    if (!glfwInit())
    Log::Error("glfwInit() Failed");

	Window::Init(false, true, "Window");
	Camera::Init(Window::width, Window::height);
	Renderer::Init({ 0.176f, 0.180f, 0.211f });
	GUI::Init();
}

Aplication::~Aplication()
{
    Renderer::Shutdown();
    Window::Shutdown();
    GUI::Shutdown();
}

void Aplication::Set_GLFW_Callbacks(GLFWkeyfun key_callback, GLFWcursorposfun mouse_callback, GLFWmousebuttonfun mouse_button_callback)
{
    glfwSetKeyCallback(Window::window, key_callback);
    glfwSetCursorPosCallback(Window::window, mouse_callback);
    glfwSetMouseButtonCallback(Window::window, mouse_button_callback);
}

void Aplication::Set_ProsessInputs_Function(void(*func)())
{
    ProsessInputs = func;
}

void Aplication::Set_OnUpdate_Function(void(*func)())
{
    OnUpdate = func;
}

void Aplication::Set_Render_Function(void(*func)())
{
    Render = func;
}

void Aplication::Set_RenderGUI_Function(void(*func)())
{
    RenderGUI = func;
}

void Aplication::Run()
{
    while (Window::IsActive())
    {
        Time::FrameStart();
        Window::PollEvents();

        if(ProsessInputs != NULL) ProsessInputs();
        if (OnUpdate != NULL) OnUpdate();

        Renderer::Clear();
        if (Render != NULL) Render();
        Renderer::DrawBatch();

        GUI::Clear();
        if (RenderGUI != NULL) RenderGUI();
        GUI::Draw();

        Window::SwapBuffers();
        Time::FrameEnd();
    }
}
