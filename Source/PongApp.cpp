#include "PongApp.h"

PongApp::PongApp(std::string appname) : GameApp(appname)
{

}

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	if (!m_Ball.CreateFromFile(renderer, "..\\gfx\\ball.png"))
		return false;

	ResetBall();

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

	m_Ball.Release();
	m_textInstruct.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	int y = 0;
	m_textInstruct.Render(renderer, 0, 0);
	m_Ball.Render(renderer, static_cast<int>(m_ball_XPos), static_cast<int>(m_ball_YPos));
}

void PongApp::AppUpdate(double dt)
{
	switch (m_Ball_dirn)
	{
	case BallLeft:
		m_ball_XPos -= m_ball_XVel*dt;
		break;
	case BallRight:
		m_ball_XPos += m_ball_XVel*dt;
		break;
	case BallUp:
		m_ball_YPos -= m_ball_YVel*dt;
		break;
	case BallDn:
		m_ball_YPos += m_ball_YVel*dt;
		break;
	}
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		m_Ball_dirn = BallLeft;
		break;
	case SDLK_RIGHT:
		m_Ball_dirn = BallRight;
		break;
	case SDLK_UP:
		m_Ball_dirn = BallUp;
		break;
	case SDLK_DOWN:
		m_Ball_dirn = BallDn;
		break;
	}

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		if (m_Ball_dirn == BallLeft)
			m_Ball_dirn = BallStop;
		break;
	case SDLK_RIGHT:
		if (m_Ball_dirn == BallRight)
			m_Ball_dirn = BallStop;
		break;
	case SDLK_UP:
		if (m_Ball_dirn == BallUp)
			m_Ball_dirn = BallStop;
		break;
	case SDLK_DOWN:
		if (m_Ball_dirn == BallDn)
			m_Ball_dirn = BallStop;
		break;
	case SDLK_SPACE:
		ResetBall();
		break;
	}

	return true;
}

void PongApp::ResetBall()
{
	BallDirection m_Ball_dirn = BallStop;

	m_ball_XPos = m_Window.GetWidth() / 2 - m_Ball.GetWidth() / 2;
	m_ball_YPos = m_Window.GetHeight() / 2 - m_Ball.GetHeight() / 2;
}


