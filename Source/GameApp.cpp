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
	AppCleanup();

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
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))
	{
		Error2MsgBox("Window Creation Failed.\n");
		return false;
	}


	if (!m_Window.CreateRenderer())
	{
		Error2MsgBox("Renderer Creation Failed.\n");
		return false;
	}

	return AppInit();
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

void GameApp::MainLoop()
{
	m_Running = true;

	// Clear the window
	m_Window.ClearWindow();

	while (m_Running)
	{
		HandleEvents();

		Render();
	}
}

void GameApp::Render()
{
	if (m_Window.CanRender())
	{
		// Get renderer and render frame then present
		Renderer& renderer = m_Window.GetRenderer();
		AppRender(renderer);
		m_Window.Present();
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

//////////////////////////////////////////////////////////////


bool PongApp::AppInit()
{
	if (m_Font.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 36, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
	{
		m_KeyPressed.CreateFromText(m_Window.GetRenderer(), "Key pressed: ", m_Font);
		m_MouseFocus.CreateFromText(m_Window.GetRenderer(), "Mouse Focus: ", m_Font);

		m_KeyFocus.CreateFromText(m_Window.GetRenderer(), "Key Focus: ", m_Font);
		m_Shown.CreateFromText(m_Window.GetRenderer(), "Shown: ", m_Font);
		m_Maximized.CreateFromText(m_Window.GetRenderer(), "Maximized: ", m_Font);

		m_Yes.CreateFromText(m_Window.GetRenderer(), "Yes", m_Font);
		m_No.CreateFromText(m_Window.GetRenderer(), "No", m_Font);
	}
	return true;
}


void PongApp::AppCleanup()
{
	m_Font.Release();
	m_KeyPressed.Release();
	m_MouseFocus.Release();
	m_Maximized.Release();
	m_KeyFocus.Release();
	m_Shown.Release();

	m_Yes.Release();
	m_No.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	int y = 0;
	m_KeyPressed.Render(renderer, 0, y);
	if (m_KeyDown == SDLK_UNKNOWN)
		m_No.Render(renderer, m_KeyPressed.GetWidth(), y);
	else
		m_Yes.Render(renderer, m_KeyPressed.GetWidth(), y);

	y += m_KeyPressed.GetHeight();

	m_MouseFocus.Render(renderer, 0, y);
	if (m_Window.hasMouseFocus())
		m_Yes.Render(renderer, m_MouseFocus.GetWidth(), y);
	else
		m_No.Render(renderer, m_MouseFocus.GetWidth(), y);

	y += m_MouseFocus.GetHeight();

	m_KeyFocus.Render(renderer, 0, y);
	if (m_Window.hasKeyboardFocus())
		m_Yes.Render(renderer, m_KeyFocus.GetWidth(), y);
	else
		m_No.Render(renderer, m_KeyFocus.GetWidth(), y);

	y += m_KeyFocus.GetHeight();

	m_Shown.Render(renderer, 0, y);
	if (m_Window.isShown())
		m_Yes.Render(renderer, m_Shown.GetWidth(), y);
	else
		m_No.Render(renderer, m_Shown.GetWidth(), y);

	y += m_Shown.GetHeight();

	m_Maximized.Render(renderer, 0, y);
	if (m_Window.isMaximized())
		m_Yes.Render(renderer, m_Maximized.GetWidth(), y);
	else
		m_No.Render(renderer, m_Maximized.GetWidth(), y);
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
	m_KeyDown = key;

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	if (m_KeyDown == key)
		m_KeyDown = SDLK_UNKNOWN;

	return true;
}
