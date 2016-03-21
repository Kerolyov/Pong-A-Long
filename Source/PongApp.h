#ifndef PongApp_h__
#define PongApp_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Font_TTF.h"

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

	double m_Ball_PosX = 0.0;
	double m_Ball_PosY = 0.0;

	double m_Ball_VelX = 200.;
	double m_Ball_VelY = 200.;

	double m_Ball_Speed = 200.;

	Texture m_Ball;
	Texture m_textInstruct;

	FontTTF m_Font;
};

#endif // PongApp_h__

