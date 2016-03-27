#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"
#include "EventHandler.h"
#include "TimeKeeper.h"

struct WindowCreationParams
{
	int iWidth=1024;			//< Required width of the window.
	int iHeight=768;			//< Required height of the window.

	// Window Params
	bool bFullscreen=false;		//< Run full-screen.
	bool Resizeable = false;	//< Whether window can be resized
	bool bOpenGL = false;		//< Create OpenGL context
	bool bBorderless = false;	//< Create window with no border
	bool bMouseGrab = false;	//< Limits mouse within bounds of window
	bool bMouseCapture = false;	//< Captures the mouse input

	// Renderer Params
	bool bSoftwareRender = false;	//< Whether use software rendering instead of GPU
	bool bVSync = false;			//< Whether to present immediately to the user (else wait for Vsync).
	bool bTextureRender = false;	//< Renderer can render to a texture as well as screen
};

class GameApp : public EventHandler
{
public:
	GameApp(std::string appname);
	virtual ~GameApp();

	int Execute(WindowCreationParams& createParam);

protected:

	void Cleanup();

	bool Init(WindowCreationParams& createParam);

	Uint32 SetRendererCreateFlags(WindowCreationParams &createParam);

	Uint32 SetWindowCreateFlags(WindowCreationParams &createParam);

	void HandleEvents();

	virtual void AppCleanup() {}
	virtual bool AppInit() { return true; }
	virtual void AppRender(Renderer& renderer) = 0;
	virtual void AppUpdate(double dt) = 0;

	void MainLoop();

	void Render();

	bool OnExit() { m_Running = false; return true; }

	void DrawFramesPerSecond(double deltaTime);

protected:
	std::string m_AppName;
	bool	m_Running = false;

	bool	m_ShowFPS = true;

	Window	m_Window;

	TimeKeeper m_Timer;
};

#endif // GameApp_h__

