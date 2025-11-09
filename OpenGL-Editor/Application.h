#pragma once

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_SDL3.h"

#include "Shader.h"
#include "Display.h"
#include "GUI.h"
#include "Vertices.h"

#include <map>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


struct ShapeData {
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	int vertexCount = 0;
	unsigned int drawMode = 0;
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
	GUI gui;

	std::map<std::string, ShapeData> shapes;

	float rotation = 0.0f;
	double prevTime = SDL_GetTicks();
	
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

