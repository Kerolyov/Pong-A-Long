#include "GameObject.h"

void GameObject::InitialiseSprite(int id, SDL_Rect size_rect, Sprite::AnchorPt anchorpt /*= Sprite::CENTRE */)
{
	m_Sprite.SetTextureID(id);

	m_Sprite.SetClipRect(size_rect);

	m_Sprite.SetAnchorPt(anchorpt);
}

SDL_Rect GameObject::GetSpriteRect() const
{
	SDL_Rect rect = m_Sprite.GetDestRect();
	rect.x += m_Position.intX();
	rect.y += m_Position.intY();

	return rect;
}


void GameObject::CheckForPlaneCollision(AXIS axis, DIRN dirn, int planePos)
{
	double& position = (axis == XAXIS) ? m_Position.x : m_Position.y;
	double& velocity = (axis == XAXIS) ? m_Velocity.x : m_Velocity.y;

	SDL_Rect obj_rect = GetSpriteRect();

	if (velocity > 0.0 && dirn == GRTERTHAN) // Going down/right
	{
		int edge = (axis == XAXIS) ? obj_rect.x + obj_rect.w : obj_rect.y + obj_rect.h;

		if (edge > planePos)
		{
			position = position - 2 * (edge - planePos);
			velocity = -velocity;
		}
	}
	else if (velocity < 0.0 && dirn == LESSTHAN)// Going up/left
	{
		int edge = (axis == XAXIS) ? obj_rect.x : obj_rect.y ;

		if (edge < planePos)
		{
			position = position + 2 * (planePos - edge);
			velocity = -velocity;
		}
	}
}

void GameObject::Update(double dt)
{
	m_Position += m_Velocity*dt;
}
