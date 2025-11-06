#pragma once

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_SDL3.h"

#include "Shader.h"
#include "Display.h"
#include "GUI.h"
#include <map>

struct ShapeData {
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	int vertexCount = 0;
	unsigned int drawMode = 0;
};

const float ver[] = {
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // unten links - Rot
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // unten rechts - Grün
		-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // oben links - Blau
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f   // oben rechts - Gelb
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
	GUI gui;

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

