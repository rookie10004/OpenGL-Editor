#include "Application.h"

void Application::LoadShape(const std::string& name, const float vertices[], size_t vertexDataSize, unsigned int drawMode)
{
	ShapeData data;
	data.vertexCount = vertexDataSize / sizeof(float) / 6;
	data.drawMode = drawMode;

	glGenVertexArrays(1, &data.VAO);
	glGenBuffers(1, &data.VBO);

	glBindVertexArray(data.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
	//Größe in Bytes übergeben
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertices, GL_STATIC_DRAW);

	//Positionsattribut
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Farbattribut
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	shapes[name] = data;
}

Application::~Application()
{
	for (auto& pair : shapes)
	{
		const std::string& name = pair.first;  // Key
		ShapeData& shape = pair.second;        // Value

		if (shape.VAO != 0) {
			glDeleteVertexArrays(1, &shape.VAO);
			shape.VAO = 0;
		}
		if (shape.VBO != 0) {
			glDeleteBuffers(1, &shape.VBO);
			shape.VBO = 0;
		}
	}

	shapes.clear();
}

void Application::Initialize()
{
	display.Initialize();
}

void Application::Setup()
{
    shader = new Shader("default.vert", "default.frag");

	LoadShape("Quadrat", vertices, sizeof(vertices), GL_TRIANGLES);
}

void Application::Update()
{
	// Hintergrund löschen und Farbe setzen
	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Shader verwenden
	shader->UseShader();

	//// Dreieck zeichnen
	//const std::string& currentSelection = gui.GetSelectedItemName();

	//// Zeichne die ausgewählte Form
	//if (shapes.count(currentSelection)) {
	//	const ShapeData& data = shapes.at(currentSelection);
	//	glBindVertexArray(data.VAO);
	//	glDrawArrays(data.drawMode, 0, data.vertexCount);
	//	glBindVertexArray(0);
	//}

	const ShapeData& data = shapes.at("Quadrat");
	glBindVertexArray(data.VAO);
	glDrawArrays(data.drawMode, 0, data.vertexCount);
    display.SwapBuffer();
}


void Application::InputHandle()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }
}