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

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void Application::Initialize()
{
	display.Initialize();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForOpenGL(display.GetWindow(), display.GetContext());
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Application::Setup()
{
    shader = new Shader("default.vert", "default.frag");

	LoadShape("Square", squareVertices, sizeof(squareVertices), GL_TRIANGLES);
	LoadShape("Triangle", triangleVertices, sizeof(triangleVertices), GL_TRIANGLES);
	LoadShape("Pyramid", pyramidVertices, sizeof(pyramidVertices), GL_TRIANGLES);
}

void Application::Update()
{
	// Hintergrund löschen und Farbe setzen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Shader verwenden
	shader->UseShader();

	double currTime = SDL_GetTicks();
	if (currTime - prevTime >= 1 / 60)
	{
		rotation += 0.5f;
		prevTime = currTime;
	}

	//Rotation
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shader->GetID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shader->GetID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shader->GetID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Zeichne die ausgewählte Form
	const std::string& currentSelection = gui.GetSelectedItemName();
	if (shapes.count(currentSelection)) {
		const ShapeData& data = shapes.at(currentSelection);
		glBindVertexArray(data.VAO);
		glDrawArrays(data.drawMode, 0, data.vertexCount);
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
    }
}