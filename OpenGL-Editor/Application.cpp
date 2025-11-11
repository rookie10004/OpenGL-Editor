#include "Application.h"

Application::~Application()
{
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

	cube.Initialize(cubeVertices, sizeof(cubeVertices), GL_TRIANGLES);
	shapeMap.emplace(cube.GetName(), &cube);

	pyramid.Initialize(pyramidVertices, sizeof(pyramidVertices), GL_TRIANGLES);
	shapeMap.emplace(pyramid.GetName(), &pyramid);

	torus.Initialize(torusVertices, sizeof(torusVertices), GL_TRIANGLES);
	shapeMap.emplace(torus.GetName(), &torus);
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

	// Zeichne die ausgewählte Form
	const std::string& currentSelection = gui.GetSelectedItemName();
	if (shapeMap.count(currentSelection)) {
		currentShape = shapeMap.at(currentSelection);
	}

	currentShape->Draw(shader, view, projection);

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

		if (event.type == SDL_EVENT_MOUSE_WHEEL)
		{
			int y = event.wheel.y;

			if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
			{
				y = -y;
			}

			float scaleStep = 0.1f;
			float factor = 1.0f + y * scaleStep;

			currentShape->Scale(glm::vec3(factor));
		}
    }
}