#pragma once

#include "imgui.h"

#include "Shader.h"
#include "Display.h"
#include "GUI.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Texture.h"

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
	Texture texture;
	GUI gui;

	// Objekte
	Mesh cube = Mesh("Cube");
	Mesh cylinder = Mesh("Cylinder");
	Mesh pyramid = Mesh("Pyramid");
	Mesh torus = Mesh("Torus");

	Mesh* currentMesh = &cube;
	std::map<std::string, Mesh*> MeshMap;

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

