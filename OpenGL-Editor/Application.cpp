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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shapes[name] = data;
}

Application::~Application()
{
	/*for (auto const& [name, data] : shapes) {
		if (data.VAO != 0) glDeleteVertexArrays(1, &data.VAO);
	}*/


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
    shader = Shader("default.vert", "default.frag");

	LoadShape("Quadrat", ver, sizeof(ver), GL_TRIANGLES);
}

void Application::Update()
{
	// Hintergrund löschen und Farbe setzen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Shader verwenden
	shader.UseShader();

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
	glDrawArrays(data.drawMode, 0, sizeof(float) / sizeof(ver) / 6);

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
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }
}