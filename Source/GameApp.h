#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"
#include "Texture.h"
#include "Font_TTF.h"

class GameApp
{
public:
	GameApp();
	~GameApp();

	int Execute();
	
private:

	void Cleanup();

	bool Init();

	void HandleEvents();

	void Render(Renderer& renderer);

	void MainLoop();

	bool	m_Running = false;

	Window	m_Window;
	Texture m_textTexture;
	Texture m_textTexture_fast;
	FontTTF m_Font;
};

#endif // GameApp_h__

