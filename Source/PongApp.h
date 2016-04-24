#ifndef PongApp_h__
#define PongApp_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Font_TTF.h"

#include "GameObject.h"

#include "TextureManager.h"
#include "Ball.h"
#include "ObjectManager.h"




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
	GameObject m_LeftPaddle;
	GameObject m_RightPaddle;

	int m_Textid = -1;
	int m_ball_id = -1;

	TextureManager m_TextureManager;
	GameObjectManager m_ObjectManager;
};

#endif // PongApp_h__

