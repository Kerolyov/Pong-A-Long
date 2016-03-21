#include "PongApp.h"

PongApp::PongApp(std::string appname) : GameApp(appname)
{

}

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	if (!m_BallTexture.CreateFromFile(renderer, "..\\gfx\\ball.png"))
		return false;

	m_Ball.SetClipRect({ 0,0, m_BallTexture.GetWidth(), m_BallTexture.GetHeight() });
	m_Ball.Reset(m_Window);

	if (m_Font.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 16, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
	{
		bool success = m_textInstruct.CreateFromText(renderer, "Arrows keys to move ball, space to reset", m_Font);

		return success;
	}
	else
		return false;
}


void PongApp::AppCleanup()
{
	m_Font.Release();

	m_BallTexture.Release();
	m_textInstruct.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	int y = 0;
	m_textInstruct.Render(renderer, 0, 0);

	m_BallTexture.Render(renderer, m_Ball.GetSpriteRect(), m_Ball.GetSprite());
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



