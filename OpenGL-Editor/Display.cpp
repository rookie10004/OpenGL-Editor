#include "Display.h"
#include "Application.h"

Display::~Display()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::Initialize()
{
    // SDL initliasieren
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized: " << SDL_GetError() << std::endl;
        return;
    }

    // SDL-OpenGL Kontext konfigurieren
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Fenster + Kontext erstellen
    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Window could not be created: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "OpenGL-Context failure: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }


}

void Display::SwapBuffer()
{
    SDL_GL_SwapWindow(window);
}
