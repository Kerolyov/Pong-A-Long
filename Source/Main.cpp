#include <string>
#include <SDL.h>

SDL_Window* g_pWindow = nullptr;
int g_WindowID = 0;
int g_Width = 0;
int g_Height = 0;

void WindowRelease()
{
	// Destroy the window
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;
}

bool WindowCreate(std::string title, int x, int y, int w, int h, Uint32 flags)
{
	WindowRelease();

	g_pWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);

	if (g_pWindow == nullptr)
		return false;

	g_Width = w;
	g_Height = h;

	//Grab window identifier 
	g_WindowID = SDL_GetWindowID(g_pWindow);

	return true;
}

bool Init()
{
	// Initialise SDL, report error if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::string err_msg = "SDL Initialisation Failed!\n";
		err_msg += SDL_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
		return false;
	}

	// Create a window, report error if window not created
	if (!WindowCreate("Test Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN))
	{
		std::string err_msg = "Window Creation Failed.\n";
		err_msg += SDL_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
		return false;
	}

	return true;
}

void Cleanup()
{
	WindowRelease();

	// Shutdown SDL
	SDL_Quit();
}

void MainLoop()
{
	// Wait for 3 seconds
	SDL_Delay(3000);
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