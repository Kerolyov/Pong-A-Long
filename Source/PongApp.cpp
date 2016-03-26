#include "PongApp.h"

PongApp::PongApp(std::string appname) : GameApp(appname)
{

}

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	// Ball Creation
	int ball_id = m_TextureManager.AddTextureFromFile(renderer, "..\\gfx\\ball.png");
	if (ball_id != -1)
		m_Ball.InitialiseSprite( ball_id, m_TextureManager.GetTextureSize(ball_id) );
 	m_Ball.Reset(m_Window);

	// Create instruction text texture
	FontTTF arialFont;
	if ( arialFont.LoadFont( "C:\\Windows\\Fonts\\ARIAL.TTF", 16, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF } ) )
		m_Textid = m_TextureManager.AddTextureFromText(renderer, "Arrows keys to move ball, space to reset", arialFont);

	return 	(ball_id != -1 && m_Textid != -1);
}


void PongApp::AppCleanup()
{
	m_TextureManager.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	m_TextureManager.RenderTexture(renderer, m_Textid, 0, 0);
	m_TextureManager.RenderTexture(renderer, m_Ball);
}

void PongApp::AppUpdate(double dt)
{
	m_Ball.Update(dt);
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		m_Ball.m_Velocity.x = -m_Ball.m_Speed;
		break;
	case SDLK_RIGHT:
		m_Ball.m_Velocity.x = m_Ball.m_Speed;
		break;
	case SDLK_UP:
		m_Ball.m_Velocity.y = -m_Ball.m_Speed;
		break;
	case SDLK_DOWN:
		m_Ball.m_Velocity.y = m_Ball.m_Speed;
		break;
	}

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		if (m_Ball.m_Velocity.x < 0.0)
			m_Ball.m_Velocity.x = 0.0;
		break;
	case SDLK_RIGHT:
		if (m_Ball.m_Velocity.x > 0.0)
			m_Ball.m_Velocity.x = 0.0;
		break;
	case SDLK_UP:
		if (m_Ball.m_Velocity.y < 0.0)
			m_Ball.m_Velocity.y = 0.0;
		break;
	case SDLK_DOWN:
		if (m_Ball.m_Velocity.y > 0.0)
			m_Ball.m_Velocity.y = 0.0;
		break;
	case SDLK_SPACE:
		m_Ball.Reset(m_Window);
		break;
	}

	return true;
}



