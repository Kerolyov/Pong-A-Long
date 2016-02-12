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

	void Render(Renderer& renderer);

	void MainLoop();

	int Execute();

	bool OnExit() { m_Running = false; return true;  }

	bool OnKeyDown(SDL_Scancode scan, SDL_Keycode key);
	bool OnKeyUp(SDL_Scancode scan, SDL_Keycode key);
	
private:
	bool	m_Running = false;
	SDL_Keycode m_KeyDown = SDLK_UNKNOWN;

	Window	m_Window;
	Texture m_KeyPressedText;
	Texture m_NoKeyPressedText;

	FontTTF m_Font;
};

#endif // GameApp_h__

