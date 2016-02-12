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
	m_KeyPressedText.Release();
	m_NoKeyPressedText.Release();

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
		m_KeyPressedText.CreateFromText(m_Window.GetRenderer(), "Key pressed", m_Font);
		m_NoKeyPressedText.CreateFromText(m_Window.GetRenderer(), "No key pressed", m_Font);
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
		if (Event.type == SDL_WINDOWEVENT && Event.window.windowID == m_Window.GetID())
			m_Window.OnEvent(Event);
		else
			OnEvent(Event);
	}
}

void GameApp::Render(Renderer& renderer)
{
	if (m_KeyDown == SDLK_UNKNOWN)
		m_NoKeyPressedText.Render(renderer,0,0);
	else
		m_KeyPressedText.Render(renderer, 0, 0);
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

	SDLK_0;
	return 0;
}

bool GameApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
	m_KeyDown = key;

	return true;
}

bool GameApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	if (m_KeyDown == key)
		m_KeyDown = SDLK_UNKNOWN;

	return true;
}
