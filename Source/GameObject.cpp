#include "GameObject.h"

SDL_Rect GameObject::GetSpriteRect() const
{
	SDL_Rect rect = m_Sprite.GetDestRect();
	rect.x += m_Position.intX();
	rect.y += m_Position.intY();

	return rect;
}


void GameObject::Update(double dt)
{
	m_Position += m_Velocity*dt;
}
