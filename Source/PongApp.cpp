#include "PongApp.h"

#include "Ball.h"

PongApp::PongApp(std::string appname) : GameApp(appname)
{

}

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	int paddle_y = m_Window.GetHeight() / 2;
	int paddle_x = 20;

	// Ball Creation
	int ball_Sprite_id = m_TextureManager.AddTextureFromFile(renderer, "..\\gfx\\ball.png");
	if (ball_Sprite_id != -1)
	{
		SDL_Rect ball_rect = m_TextureManager.GetTextureSize(ball_Sprite_id);
		m_Ball.InitialiseSprite(ball_Sprite_id, ball_rect);
		m_Ball.Reset(m_Window);

		Ball* pBall = new Ball();
		pBall->InitialiseSprite(ball_Sprite_id, ball_rect);
		pBall->Reset(m_Window);
		m_ball_id = m_ObjectManager.AddObject( std::unique_ptr<GameObject>(pBall) );			
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
		m_Textid = m_TextureManager.AddTextureFromText(renderer, "Press space to reset ball with random direction", arialFont);

	return 	(ball_Sprite_id != -1 && paddle_id != -1 && m_Textid != -1);
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

	m_ObjectManager.RenderObjects(m_TextureManager, renderer);
}

void PongApp::AppUpdate(double dt)
{
	m_ObjectManager.UpdateObjects(dt);

	m_Ball.Update(dt);
	m_LeftPaddle.Update(dt);
	m_RightPaddle.Update(dt);

	m_Ball.CheckForPlaneCollision(YAXIS, LESSTHAN, 0);
	m_Ball.CheckForPlaneCollision(YAXIS, GRTERTHAN, m_Window.GetHeight() );

	m_Ball.CheckForPlaneCollision(XAXIS, LESSTHAN, 0);
	m_Ball.CheckForPlaneCollision(XAXIS, GRTERTHAN, m_Window.GetWidth());
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
// 	switch (key)
// 	{
// 	case SDLK_LEFT:
// 		m_Ball.m_Velocity.x = -m_Ball.m_Speed;
// 		break;
// 	case SDLK_RIGHT:
// 		m_Ball.m_Velocity.x = m_Ball.m_Speed;
// 		break;
// 	case SDLK_UP:
// 		m_Ball.m_Velocity.y = -m_Ball.m_Speed;
// 		break;
// 	case SDLK_DOWN:
// 		m_Ball.m_Velocity.y = m_Ball.m_Speed;
// 		break;
// 	}

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	switch (key)
	{
// 	case SDLK_LEFT:
// 		if (m_Ball.m_Velocity.x < 0.0)
// 			m_Ball.m_Velocity.x = 0.0;
// 		break;
// 	case SDLK_RIGHT:
// 		if (m_Ball.m_Velocity.x > 0.0)
// 			m_Ball.m_Velocity.x = 0.0;
// 		break;
// 	case SDLK_UP:
// 		if (m_Ball.m_Velocity.y < 0.0)
// 			m_Ball.m_Velocity.y = 0.0;
// 		break;
// 	case SDLK_DOWN:
// 		if (m_Ball.m_Velocity.y > 0.0)
// 			m_Ball.m_Velocity.y = 0.0;
// 		break;
	case SDLK_SPACE:
		m_Ball.Reset(m_Window);
		Ball* pBall = dynamic_cast<Ball*>(m_ObjectManager.GetObject(m_ball_id).get());
		if (pBall) pBall->Reset(m_Window);
		break;
	}

	return true;
}



