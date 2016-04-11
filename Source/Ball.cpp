#include "Ball.h"
#include "Window.h"


Ball::Ball() : GameObject()
{

}

Ball::~Ball()
{

}

void Ball::Reset(Window& window)
{
	m_Velocity = Vec2D();

	m_Position.x = window.GetWidth() / 2;
	m_Position.y = window.GetHeight() / 2;
}
