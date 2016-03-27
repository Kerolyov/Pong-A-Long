#include "PongApp.h"

int main(int argc, char *argv[])
{
	WindowCreationParams createParam;
	createParam.bFullscreen = true;

	PongApp app("Moving Ball");
	return app.Execute(createParam);
}