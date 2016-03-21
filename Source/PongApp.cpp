#include "PongApp.h"

PongApp::PongApp(std::string appname) : GameApp(appname)
{

}

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	// Ball Creation
	if (!m_Ball.CreateFromFile(renderer, "..\\gfx\\ball.png"))
		return false;

	ResetBall();

	// Create instruction text texture
	FontTTF arialFont;

	if (arialFont.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 16, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
		return m_textInstruct.CreateFromText(renderer, "Arrows keys to move ball, space to reset", arialFont);

	return false;
}




void PongApp::AppCleanup()
{
	m_Ball.Release();
	m_textInstruct.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	m_textInstruct.Render(renderer, 0, 0);
	m_Ball.Render(renderer, static_cast<int>(m_Ball_PosX), static_cast<int>(m_Ball_PosY));
}

void PongApp::AppUpdate(double dt)
{
	m_Ball_PosX += m_Ball_VelX*dt;
	m_Ball_PosY += m_Ball_VelY*dt;
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		m_Ball_VelX = -m_Ball_Speed;
		break;
	case SDLK_RIGHT:
		m_Ball_VelX = m_Ball_Speed;
		break;
	case SDLK_UP:
		m_Ball_VelY = -m_Ball_Speed;
		break;
	case SDLK_DOWN:
		m_Ball_VelY = m_Ball_Speed;
		break;
	}

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		if (m_Ball_VelX < 0.0)
			m_Ball_VelX = 0.0;
		break;
	case SDLK_RIGHT:
		if (m_Ball_VelX > 0.0)
			m_Ball_VelX = 0.0;
		break;
	case SDLK_UP:
		if (m_Ball_VelY < 0.0)
			m_Ball_VelY = 0.0;
		break;
	case SDLK_DOWN:
		if (m_Ball_VelY > 0.0)
			m_Ball_VelY = 0.0;
		break;
	case SDLK_SPACE:
		ResetBall();
		break;
	}

	return true;
}

void PongApp::ResetBall()
{
	m_Ball_VelX = 0.0;
	m_Ball_VelY = 0.0;

	m_Ball_PosX = m_Window.GetWidth() / 2 - m_Ball.GetWidth() / 2;
	m_Ball_PosY = m_Window.GetHeight() / 2 - m_Ball.GetHeight() / 2;
}


