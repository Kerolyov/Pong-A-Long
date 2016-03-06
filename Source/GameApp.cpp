#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>

#include "SDLErrorReport.h"
#include "TimeKeeper.h"

GameApp::GameApp(std::string appname) : m_AppName(appname)
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
	if (!m_Window.Create(m_AppName,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE*/))
	{
		Error2MsgBox("Window Creation Failed.\n");
		return false;
	}

	// Creates a renderer and clears the window
	if (!m_Window.CreateRenderer())
	{
		Error2MsgBox("Renderer Creation Failed.\n");
		return false;
	}

	TimeKeeper::initialize();

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

	double maxFrameTime = 1.0 / m_minFPS;
	double minFrameTime = 1.0 / m_maxFPS;

	double timeElapsed = 0.0;

	// Application will indicate quit by setting m_Running to false
	// until then we loop thro event handling and rendering each frame
	while (m_Running)
	{
		HandleEvents();

		// Gets time since last frame
		TimeKeeper::update();
		double deltaTime = TimeKeeper::getDeltaTime();

		// Prevents the deltatime going beyond a given value
		if (deltaTime > maxFrameTime)
		{
			deltaTime = maxFrameTime;
			m_MissedFrames++;
		}

		timeElapsed += deltaTime;

		// Only update once every 1/100 seconds.
		// timeElapsed set to zero at end of Mainloop
		if (timeElapsed >= minFrameTime)
		{
			AppUpdate(timeElapsed);

			if (m_ShowFPS)
				DrawFramesPerSecond(timeElapsed);

			Render();

			timeElapsed = 0.0;
		}
	}
}

void GameApp::Render()
{
	// If we have valid window & renderer then render the frame
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

void GameApp::DrawFramesPerSecond(double deltaTime)
{
	// Make static so the variables persist even after
	// the function returns.
	static int		frameCnt = 0;
	static double	timeElapsed = 0.0f;

	// Function called implies a new frame, so increment
	// the frame count.
	++frameCnt;

	// Also increment how much time has passed since the
	// last frame.  
	timeElapsed += deltaTime;

	// Has a second passed?
	if (timeElapsed >= 1.0f)
	{
		// Yes, so compute the frames per second.
		// FPS = frameCnt / timeElapsed, but since we

		// Add the frames per second string to the main
		// window caption--that is, we'll display the frames
		// per second in the window's caption bar.

		std::stringstream strm;
		strm << m_AppName << "--Frames Per Second = " << static_cast<int>(frameCnt/timeElapsed);
		strm << ", missed " << m_MissedFrames << " frames";

		// Now set the new caption to the main window.
		m_Window.SetTitle(strm.str());

		// Reset the counters to prepare for the next time
		// we compute the frames per second.
		frameCnt = 0;
		timeElapsed = 0.0f;
	}
}


