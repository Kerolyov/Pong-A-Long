#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"
#include "EventHandler.h"
#include "TimeKeeper.h"

class GameApp : public EventHandler
{
public:
	GameApp(std::string appname);
	virtual ~GameApp();

	int Execute();

protected:

	void Cleanup();

	bool Init();

	void HandleEvents();

	virtual void AppCleanup() {}
	virtual bool AppInit() { return true; }
	virtual void AppRender(Renderer& renderer) = 0;
	virtual void AppUpdate(double dt) = 0;

	void MainLoop();

	void Render();

	bool OnExit() { m_Running = false; return true; }

	void DrawFramesPerSecond();

protected:
	std::string m_AppName;
	bool	m_Running = false;

	bool	m_ShowFPS = true;

	Window	m_Window;

	TimeKeeper m_Timer;
};

#endif // GameApp_h__

