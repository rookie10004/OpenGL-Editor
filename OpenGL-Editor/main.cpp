#include "Application.h"

int main(void) {
	Application app;

	app.Initialize();
	app.Setup();

	while(app.GetIsRunning()) {
		app.InputHandle();
		app.Render();
	}

	return 0;
}