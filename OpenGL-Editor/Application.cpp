#include "Application.h"

Application::~Application()
{
	shapeMap.clear();

	delete shader;

	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &TCB);
	glDeleteRenderbuffers(1, &RBO);

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

	SetupFBO();

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

void Application::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, width - 200, height);

	// Hintergrund löschen und Farbe setzen
	glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Rotation
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)(width - 200) / (float)height, 0.1f, 100.0f);

	// Zeichne die ausgewählte Form
	const std::string& currentSelection = gui.GetSelectedItemName();
	if (shapeMap.count(currentSelection)) {
		currentShape = shapeMap.at(currentSelection);
	}

	currentShape->Draw(shader, view, projection);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// GUI zeichnen
	gui.Draw(display, TCB, currentShape);

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

void Application::SetupFBO()
{
	// Generiere FBO, Textur und RBO
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Generiere Textur-Attachment
	glGenTextures(1, &TCB);
	glBindTexture(GL_TEXTURE_2D, TCB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width - 200, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TCB, 0);

	// Generiere Renderbuffer-Objekt für Tiefe und Stencil
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width - 200, height); 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	// Prüfe auf Vollständigkeit
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
