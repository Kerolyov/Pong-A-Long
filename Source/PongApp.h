#ifndef PongApp_h__
#define PongApp_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Font_TTF.h"

class PongApp : public GameApp
{
public:
	PongApp() {}
	virtual ~PongApp(){}

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

#endif // PongApp_h__

