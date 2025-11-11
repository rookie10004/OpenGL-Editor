#pragma once

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_SDL3.h"

#include "Shader.h"
#include "Display.h"
#include "GUI.h"
#include "Vertices.h"
#include "Shape.h"

#include <map>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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

	Shape cube = Shape("Cube");
	Shape cylinder = Shape("Cylinder");
	Shape pyramid = Shape("Pyramid");
	Shape torus = Shape("Torus");

	Shape* currentShape = &cube;
	std::map<std::string, Shape*> shapeMap;

public:
	Application() : display(title, width, height) {};
	~Application();

	void Initialize();
	void Setup();
	void Update();
	void InputHandle();
	bool GetIsRunning() const { return isRunning; };
};

