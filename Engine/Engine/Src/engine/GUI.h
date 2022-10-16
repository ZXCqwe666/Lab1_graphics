#pragma once

#include "imgui/imgui.h"

class GUI
{
private:
	static ImGuiIO io;

public:
	static void Init();
	static void Shutdown();

	static void Clear();
	static void Draw();
};
