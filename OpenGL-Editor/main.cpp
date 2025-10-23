#include "Application.h"

int main(void) {
	Application app;

	app.Initialize();
	app.Setup();

	while(app.getIsRunning()) {
		app.InputHandle();


	}
}