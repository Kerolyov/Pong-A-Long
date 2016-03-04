#ifndef PongApp_h__
#define PongApp_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Font_TTF.h"

class PongApp : public GameApp
{
public:
	PongApp() {}
	virtual ~PongApp() {}

	bool AppInit();
	void AppCleanup();

	void AppRender(Renderer& renderer);

private:
	Texture m_textTexture;
	Texture m_textTexture_fast;

	FontTTF m_Font;
};

#endif // PongApp_h__

