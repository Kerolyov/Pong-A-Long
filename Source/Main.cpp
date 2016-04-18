#include "PongApp.h"

int main(int argc, char *argv[])
{
	WindowCreationParams createParam;

	PongApp app("Moving Ball");
	return app.Execute(createParam);
}