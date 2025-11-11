#include "Application.h"

Application::~Application()
{
	for (auto& pair : shapeMap)
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
	shapeMap.clear();

	delete shader;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void Application::Initialize()
{
	display.Initialize();

	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForOpenGL(display.GetWindow(), display.GetContext());
	ImGui_ImplOpenGL3_Init("#version 330 core");

	shapeMap.emplace(square.GetName(), square.Initialize(squareVertices, sizeof(squareVertices), GL_TRIANGLES));
	shapeMap.emplace(triangle.GetName(), triangle.Initialize(triangleVertices, sizeof(triangleVertices), GL_TRIANGLES));
	shapeMap.emplace(pyramid.GetName(), pyramid.Initialize(pyramidVertices, sizeof(pyramidVertices), GL_TRIANGLES));
}

void Application::Setup()
{
    shader = new Shader("default.vert", "default.frag");
}

void Application::Update()
{
	// Hintergrund löschen und Farbe setzen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Rotation
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	currentShape->Draw(shader, view, projection);

	// Zeichne die ausgewählte Form
	const std::string& currentSelection = gui.GetSelectedItemName();
	if (shapeMap.count(currentSelection)) {
		const ShapeData& data = shapeMap.at(currentSelection);
		glBindVertexArray(data.VAO);
		glDrawArrays(data.drawMode, 0, data.vertexCount);
		currentShape = data.shape;
	}

	// ImGui Frame Start
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	// GUI zeichnen
	gui.Draw();

	// ImGui Frame Ende und Rendern
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    display.SwapBuffer();
}


void Application::InputHandle()
{
    while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }

		if (event.type == SDL_EVENT_MOUSE_MOTION && (event.motion.state & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)))
		{
			float mouseX, mouseY;
			int buttons = SDL_GetMouseState(&mouseX, &mouseY);

			float xOffset = (float)event.motion.xrel;
			float yOffset = (float)event.motion.yrel;

			currentShape->Rotate(xOffset, yOffset);
		}
    }
}