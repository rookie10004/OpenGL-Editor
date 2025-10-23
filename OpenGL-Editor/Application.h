#pragma once

#include <SDL3/sdl.h>

#include "Display.h"

class Application
{
private:
	int width = 800;
	int height = 600;
	const char* title = "OpenGL-Editor";
	bool isRunning = true;

public:
	void Initialize();
	void Setup();
	void InputHandle();
	bool getIsRunning() { return isRunning; };
};

