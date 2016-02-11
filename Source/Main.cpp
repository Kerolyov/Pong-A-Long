#include <string>
#include <SDL.h>
#include <SDL_image.h>

// Window
SDL_Window* g_pWindow = nullptr;
int g_WindowID = 0;
int g_Width = 0;
int g_Height = 0;

//Renderer
SDL_Renderer* g_pRenderer = nullptr;
SDL_Color g_BackgroundColor = SDL_Color{ 0x00, 0x00, 0x00, 0xFF };

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

void RendererRelease()
{
	SDL_DestroyRenderer(g_pRenderer);
	g_pRenderer = nullptr;
}

void RendererClearBackBuffer()
{
	SDL_SetRenderDrawColor(g_pRenderer, g_BackgroundColor.r, g_BackgroundColor.g, g_BackgroundColor.b, g_BackgroundColor.a);
	SDL_RenderClear(g_pRenderer);
}

bool CreateRenderer(int index, Uint32 flags)
{
	if (!g_pWindow)
		return false;

	RendererRelease();

	g_pRenderer = SDL_CreateRenderer(g_pWindow, index, flags);
	if (g_pRenderer == nullptr)
		return false;

	RendererClearBackBuffer();

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

	if (!CreateRenderer(-1, SDL_RENDERER_ACCELERATED))
	{
		Err2MsgBox("Renderer Creation Failed.\n");
		return false;
	}

	return true;
}

void Cleanup()
{
	TextureRelease();
	RendererRelease();
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
		g_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, pSurface);
		SDL_FreeSurface(pSurface);

		if (g_pTexture != nullptr)
		{
			g_Width = pSurface->w;
			g_Height = pSurface->h;
		}
	}
}

void MainLoop()
{
	// Load the image
	LoadTestImage("../Gfx/HelloWorld.png");

	// Clear the window
	RendererClearBackBuffer();

	if (g_pRenderer && g_pTexture)
		SDL_RenderCopy(g_pRenderer, g_pTexture, nullptr, nullptr);

	SDL_RenderPresent(g_pRenderer);

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