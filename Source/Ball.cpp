#include "Ball.h"
#include "Window.h"

#include <random> 

Ball::Ball() : GameObject()
{

}

Ball::~Ball()
{

}

void Ball::Reset(Window& window)
{
	static const double angl_conv = 2* 3.14159265/360;
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution(0, 360);

	double angle = distribution(generator);

	double x = m_Speed*cos(angle*angl_conv);
	double y = m_Speed*sin(angle*angl_conv);

	m_Velocity = Vec2D( x, y );

	m_Position.x = window.GetWidth() / 2;
	m_Position.y = window.GetHeight() / 2;
}
