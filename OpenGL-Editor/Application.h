#pragma once

#include "imgui.h"

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
	int settingsWidth = 200;
	const char* title = "OpenGL-Editor";
	bool isRunning = true;

	Display display;
	Shader* shader = nullptr;
	SDL_Event event;
	GUI gui;

	// Objekte
	Shape cube = Shape("Cube");
	Shape cylinder = Shape("Cylinder");
	Shape pyramid = Shape("Pyramid");
	Shape torus = Shape("Torus");

	Shape* currentShape = &cube;
	std::map<std::string, Shape*> shapeMap;

	unsigned int FBO; // Frame Buffer
	unsigned int TCB; // Texture Color Buffer
	unsigned int RBO; // Render Buffer

	// FPS Attribute
	float lastFrameTime = 0.0f;
	float fpsTimer = 0.0f;
	int frameCount = 0;
	float FPS = 60;


public:
	Application() : display(title, width, height, settingsWidth) {};
	~Application();

	void Initialize();
	void Setup();
	void Render();
	void InputHandle();
	bool GetIsRunning() const { return isRunning; }
	void SetupFBO();
	unsigned int GetViewPortTextureID() const { return TCB; }
};

