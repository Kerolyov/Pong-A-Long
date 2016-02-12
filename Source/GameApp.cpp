#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDLErrorReport.h"


GameApp::GameApp()
{

}

GameApp::~GameApp()
{
	Cleanup();
}

void GameApp::Cleanup()
{
	// App specific cleanup
	m_Font.Release();
	m_textTexture.Release();
	m_textTexture_fast.Release();

	// Generic cleanup
	m_Window.Release();

	// Shutdown SDL
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool GameApp::Init()
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


	//Initialize SDL_ttf 
	if (TTF_Init() == -1)
	{
		std::string err_msg = "SDL_ttf could not initialize!\n";
		err_msg += TTF_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", err_msg.c_str(), nullptr);
		return false;
	}

	// Create a window, report error if window not created
	if (!m_Window.Create("Test Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN))
	{
		Error2MsgBox("Window Creation Failed.\n");
		return false;
	}


	if (!m_Window.CreateRenderer())
	{
		Error2MsgBox("Renderer Creation Failed.\n");
		return false;
	}

	if (m_Font.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 36, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
	{
		m_textTexture.CreateFromText(m_Window.GetRenderer(), "Quality render text", m_Font);
		m_textTexture_fast.CreateFromText_Fast(m_Window.GetRenderer(), "Fast render text", m_Font);
	}

	// Load the image
	//m_Texture.CreateFromFile(m_Window.GetRenderer(), "../Gfx/HelloWorld.png");

	return true;
}

void GameApp::HandleEvents()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_QUIT)
			m_Running = false;
	}
}

void GameApp::Render(Renderer& renderer)
{
	m_textTexture.Render(renderer, 0, 0);
	m_textTexture_fast.Render(renderer, 0, m_textTexture.GetHeight());
}

void GameApp::MainLoop()
{
	m_Running = true;

	// Clear the window
	m_Window.ClearWindow();

	while (m_Running)
	{
		HandleEvents();

		if (m_Window.CanRender())
		{
			// Get renderer and render frame then present
			Renderer& renderer = m_Window.GetRenderer();
			Render(renderer);
			m_Window.Present();
		}
	}
}

int GameApp::Execute()
{
	// Initialise SDL and create window
	if (!Init())
		return -1;

	MainLoop();

	Cleanup();

	return 0;
}
