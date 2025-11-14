#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <iostream>

class Display
{
private:
	int width;
	int height;
	int settingsWidth;
	const char* title;

	SDL_Window* window;
	SDL_GLContext context;
	GLenum glewError;

public:
	Display() = default;
	Display(const char* title, int width, int height, int settingsWidth) : title(title), width(width), height(height), settingsWidth(settingsWidth) {};
	~Display();

	void Initialize();
	void SwapBuffer();
	SDL_Window* GetWindow() { return window; }
	SDL_GLContext GetContext() { return context; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetSettingsWidth() { return settingsWidth; }
};