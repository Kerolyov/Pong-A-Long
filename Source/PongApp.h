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

	enum BallDirection { BallUp, BallDn, BallLeft , BallRight, BallStop };

	BallDirection m_Ball_dirn = BallStop;

	double m_ball_XPos = 0.0;
	double m_ball_YPos = 0.0;

	double m_ball_XVel = 50.;
	double m_ball_YVel = 50.;

	Texture m_Ball;
	Texture m_textInstruct;

	FontTTF m_Font;
};

#endif // PongApp_h__

