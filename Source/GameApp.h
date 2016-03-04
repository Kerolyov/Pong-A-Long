#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"

class GameApp
{
public:
	GameApp();
	~GameApp();

	int Execute();

protected:

	void Cleanup();

	bool Init();

	void HandleEvents();

	virtual void AppCleanup() {}
	virtual bool AppInit() { return true; }
	virtual void AppRender(Renderer& renderer) = 0;

	void MainLoop();

	void Render();

	bool OnExit() { m_Running = false; return true; }

protected:
	bool	m_Running = false;

	Window	m_Window;
};

#endif // GameApp_h__

