#include "PongApp.h"

PongApp::PongApp(std::string appname) : GameApp(appname)
{

}

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	int paddle_y = m_Window.GetHeight() / 2;
	int paddle_x = 20;

	// Ball Creation
	int ball_id = m_TextureManager.AddTextureFromFile(renderer, "..\\gfx\\ball.png");
	if (ball_id != -1)
	{
		SDL_Rect ball_rect = m_TextureManager.GetTextureSize(ball_id);
		m_Ball.InitialiseSprite(ball_id, ball_rect);
		m_Ball.Reset(m_Window);

		m_Ball.AddConstraint( std::unique_ptr<Constraint>(new ClampMin(Constraint::AXIS_Y, ball_rect.h / 2)) );
		m_Ball.AddConstraint( std::unique_ptr<Constraint>(new ClampMax(Constraint::AXIS_Y, m_Window.GetHeight() - ball_rect.h / 2)) );
	}

	// Paddle creation
	int paddle_id = m_TextureManager.AddTextureFromFile(renderer, "..\\gfx\\paddle.png");
	if (paddle_id != -1)
	{
		m_LeftPaddle.InitialiseSprite(paddle_id, m_TextureManager.GetTextureSize(paddle_id), Sprite::LEFT);
		m_LeftPaddle.SetPosition(Vec2D(paddle_x, paddle_y)); 

		m_RightPaddle.InitialiseSprite(paddle_id, m_TextureManager.GetTextureSize(paddle_id), Sprite::RIGHT);
		m_RightPaddle.SetPosition(Vec2D(m_Window.GetWidth() - paddle_x, paddle_y));
	}
	
	// Create instruction text texture
	FontTTF arialFont;
	if ( arialFont.LoadFont( "C:\\Windows\\Fonts\\ARIAL.TTF", 16, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF } ) )
		m_Textid = m_TextureManager.AddTextureFromText(renderer, "Arrows keys to move ball, space to reset", arialFont);

	return 	(ball_id != -1 && paddle_id != -1 && m_Textid != -1);
}


void PongApp::AppCleanup()
{
	m_TextureManager.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	m_TextureManager.RenderTexture(renderer, m_Textid, 0, 0);

	m_TextureManager.RenderTexture(renderer, m_Ball);
	m_TextureManager.RenderTexture(renderer, m_LeftPaddle);
	m_TextureManager.RenderTexture(renderer, m_RightPaddle);
}

void PongApp::AppUpdate(double dt)
{
	m_Ball.Update(dt);
	m_LeftPaddle.Update(dt);
	m_RightPaddle.Update(dt);
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



