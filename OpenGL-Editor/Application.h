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

inline float verticesT[] = {
	-0.5f, -0.5f, 0.0f, 0, 0, 0,// Vertex 1 (bottom-left)
	 0.5f, -0.5f, 0.0f, 0, 0, 0,// Vertex 2 (bottom-right)
	 0.0f,  0.5f, 0.0f,  0, 0, 0// Vertex 3 (top)
};

class Application
{
private:
	int width = 800;
	int height = 600;
	const char* title = "OpenGL-Editor";
	bool isRunning = true;

	Display display;
	Shader shader;
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

