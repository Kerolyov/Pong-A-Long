#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"
#include "Texture.h"

class GameApp
{
public:
	GameApp();
	~GameApp();

	void Cleanup();

	bool Init();

	void HandleEvents();

	void Render(Renderer& renderer);

	void MainLoop();

	int Execute();
	
private:
	bool	m_Running = false;

	Window	m_Window;
	Texture m_Texture;
};

#endif // GameApp_h__

