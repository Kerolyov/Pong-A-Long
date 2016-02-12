#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"
#include "Texture.h"
#include "Font_TTF.h"
#include "EventHandler.h"

class GameApp : public EventHandler
{
public:
	GameApp();
	virtual ~GameApp();

	void Cleanup();

	bool Init();

	void HandleEvents();

	virtual void AppCleanup() {}
	virtual bool AppInit() { return true; }
	virtual void AppRender(Renderer& renderer) = 0;

	void MainLoop();

	void Render();

	int Execute();

	bool OnExit() { m_Running = false; return true;  }
	
protected:
	bool	m_Running = false;

	Window	m_Window;
};

class PongApp : public GameApp
{
public:
	PongApp() {}
	virtual ~PongApp()
	{

	}

	bool AppInit();
	void AppCleanup();

	void AppRender(Renderer& renderer);

	bool OnKeyDown(SDL_Scancode scan, SDL_Keycode key);
	bool OnKeyUp(SDL_Scancode scan, SDL_Keycode key);

private:
	SDL_Keycode m_KeyDown = SDLK_UNKNOWN;
	Texture m_KeyPressed;
	Texture m_MouseFocus;
	Texture m_KeyFocus;
	Texture m_Shown;
	Texture m_Maximized;

	Texture m_Yes;
	Texture m_No;

	FontTTF m_Font;
};

#endif // GameApp_h__

