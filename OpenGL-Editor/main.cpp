#include "Application.h"

int main(void) {
	Application app;

	app.Initialize();
	app.Setup();

	while(app.GetIsRunning()) {
		app.InputHandle();
		app.Update();
	}

	return 0;
}