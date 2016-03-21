#ifndef PongApp_h__
#define PongApp_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Font_TTF.h"

#include "GameObject.h"

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
	void ResetBall();

	Vec2D m_Ball_Pos;
	Vec2D m_Ball_Vel;

	double m_Ball_speed = 200.;

	Texture m_Ball;
	Texture m_textInstruct;

	FontTTF m_Font;
};

#endif // PongApp_h__

