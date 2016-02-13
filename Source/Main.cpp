#include <string>
#include <SDL.h>

SDL_Window* g_pWindow = nullptr;

int main(int argc, char *argv[])
{
	// Initialise SDL, report error if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::string err_msg = "SDL Initialisation Failed!\n";
		err_msg += SDL_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
		return -1;
	}

	// Create a window
	g_pWindow = SDL_CreateWindow("Test Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN);

	// Report error if window not created
	if (g_pWindow == nullptr)
	{
		std::string err_msg = "Window Creation Failed!\n";
		err_msg += SDL_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
		return -1;
	}

	// Wait for 3 seconds
	SDL_Delay(3000);

	// Destroy the window
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;

	// Shutdown SDL
	SDL_Quit();
	return 0;
}