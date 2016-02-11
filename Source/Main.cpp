#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"
#include "Texture.h"
#include "Window.h"
#include "SDLErrorReport.h"

bool g_Running = false;

Window g_Window;
Texture g_Texture;

bool Init()
{
	// Initialise SDL, report error if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Error2MsgBox("SDL Initialisation Failed!\n");
		return false;
	}

	//Initialize PNG/JPG loading 
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::string err_msg = "SDL_image could not initialize!\n";
		err_msg += IMG_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
		return false;
	}

	// Create a window, report error if window not created
	if (!g_Window.Create("Test Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN))
	{
		Error2MsgBox("Window Creation Failed.\n");
		return false;
	}

	if (!g_Window.CreateRenderer())
	{
		Error2MsgBox("Renderer Creation Failed.\n");
		return false;
	}

	return true;
}

void Cleanup()
{
	// Shutdown SDL
	IMG_Quit();
	SDL_Quit();
}



void HandleEvents()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_QUIT)
			g_Running = false;
	}
}



void Render(Renderer& renderer)
{
	g_Texture.Render(renderer);
}

void MainLoop()
{
	// Load the image
	g_Texture.CreateFromFile(g_Window.GetRenderer(), "../Gfx/HelloWorld.png");

	g_Running = true;

	// Clear the window
	g_Window.ClearWindow();

	while (g_Running)
	{
		HandleEvents();

		if (g_Window.CanRender())
		{
			// Get renderer
			Renderer& renderer = g_Window.GetRenderer();
			Render(renderer);
			g_Window.Present();
		}
	}
}

int main(int argc, char *argv[])
{
	// Initialise SDL and create window
	if (!Init())
		return -1;

	MainLoop();

	Cleanup();

	return 0;
}