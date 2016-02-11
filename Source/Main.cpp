#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"

bool g_Running = false;

// Window
SDL_Window* g_pWindow = nullptr;
int g_WindowID = 0;
int g_Width = 0;
int g_Height = 0;


Renderer g_Renderer;
//Renderer
//SDL_Renderer* g_pRenderer = nullptr;
//SDL_Color g_BackgroundColor = SDL_Color{ 0x00, 0x00, 0x00, 0xFF };

//Texture
SDL_Texture*  g_pTexture = nullptr;
int g_TextureWidth = 0;
int g_TextureHeight = 0;

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


void TextureRelease()
{
	SDL_DestroyTexture(g_pTexture);
	g_pTexture = nullptr;
	g_Width = 0;
	g_Height = 0;
}

void Err2MsgBox(std::string err_msg)
{
	err_msg += SDL_GetError();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
}

bool Init()
{
	// Initialise SDL, report error if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Err2MsgBox("SDL Initialisation Failed!\n");
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
	if (!WindowCreate("Test Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN))
	{
		Err2MsgBox("Window Creation Failed.\n");
		return false;
	}

	//if (!CreateRenderer(-1, SDL_RENDERER_ACCELERATED))
	if (!g_Renderer.Create(g_pWindow))
	{
		Err2MsgBox("Renderer Creation Failed.\n");
		return false;
	}

	return true;
}

void Cleanup()
{
	TextureRelease();
	g_Renderer.Release();
	WindowRelease();

	// Shutdown SDL
	IMG_Quit();
	SDL_Quit();
}

void LoadTestImage(std::string filename)
{
	SDL_Surface* pSurface = nullptr;
	pSurface = IMG_Load(filename.c_str());

	if (!pSurface)
	{
		Err2MsgBox("Could not load texture from file.\n");
		return;
	}
	else
	{
		TextureRelease();
		g_pTexture = SDL_CreateTextureFromSurface(g_Renderer.GetRenderPtr(), pSurface);
		SDL_FreeSurface(pSurface);

		if (g_pTexture != nullptr)
		{
			g_Width = pSurface->w;
			g_Height = pSurface->h;
		}
	}
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

void Render()
{
	if (g_Renderer.GetRenderPtr() && g_pTexture)
		SDL_RenderCopy(g_Renderer.GetRenderPtr(), g_pTexture, nullptr, nullptr);

	// Display backbuffer and clear new one ready for next frame
	g_Renderer.Present();
}

void MainLoop()
{
	// Load the image
	LoadTestImage("../Gfx/HelloWorld.png");

	g_Running = true;

	// Clear the window
	g_Renderer.ClearBackBuffer();

	while (g_Running)
	{
		HandleEvents();

		Render();
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