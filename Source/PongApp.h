#ifndef PongApp_h__
#define PongApp_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Font_TTF.h"

#include "GameObject.h"

class Ball : public GameObject
{
public:
	friend class PongApp;
	Ball() : GameObject() {}
	virtual ~Ball() {}

	void Reset(Window& window)
	{
		m_Velocity = Vec2D();

		m_Position.x = window.GetWidth() / 2;
		m_Position.y = window.GetHeight() / 2;
	}
	
private:
	double m_Speed = 200.;
};

// ------------------------------------------

class PongApp : public GameApp
{
public:
	PongApp(std::string appname);
	virtual ~PongApp(){}

	bool AppInit();
	void AppCleanup();

	void AppRender(Renderer& renderer);

	void AppUpdate(double dt);

	bool OnKeyDown(SDL_Scancode scan, SDL_Keycode key);
	bool OnKeyUp(SDL_Scancode scan, SDL_Keycode key);

private:
	Ball m_Ball;

	Texture m_BallTexture;
	Texture m_textInstruct;

	FontTTF m_Font;
};

#endif // PongApp_h__

