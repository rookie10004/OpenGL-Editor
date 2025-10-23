#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class Display
{
private:
	int width;
	int height;
	const char* title;
	SDL_Window* window;
	SDL_GLContext context;

public:
	Display(const char* title, int width, int height) : title(title), width(width), height(height) { };
	~Display();

	void Initialize();
	void SwapBuffer();

};

