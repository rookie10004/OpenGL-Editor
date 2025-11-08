#pragma once

#include "Shader.h"
#include "Display.h"
#include <map>

struct ShapeData {
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	int vertexCount = 0;
	unsigned int drawMode = 0;
};

inline float vertices[] = {
	 -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // unten links - Rot
   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // unten rechts - Grün
   0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   // oben rechts - Gelb

   // Zweites Dreieck
   -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // unten links - Rot
	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   // oben rechts - Gelb
   -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // oben links - Blau
};

class Application
{
private:
	int width = 800;
	int height = 600;
	const char* title = "OpenGL-Editor";
	bool isRunning = true;

	Display display;
	Shader* shader = nullptr;
	SDL_Event event; 

	std::map<std::string, ShapeData> shapes;
	
	void LoadShape(const std::string& name, const float vertices[], size_t vertexDataSze, unsigned int drawMode);

public:
	Application() : display(title, width, height) {};
	~Application();

	void Initialize();
	void Setup();
	void Update();
	void InputHandle();
	bool GetIsRunning() const { return isRunning; };
};

