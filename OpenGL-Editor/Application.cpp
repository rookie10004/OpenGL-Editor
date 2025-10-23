#include "Application.h"

void Application::Initialize()
{
	Display display(title, width, height);
	display.Initialize();
}

void Application::Setup()
{
}

void Application::InputHandle()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }
}