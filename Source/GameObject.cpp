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


void GameObject::Update(double dt)
{
	m_Position += m_Velocity*dt;

	for (std::unique_ptr<Constraint>& pConstraint : m_Constraints)
	{
		if (pConstraint) 
			pConstraint->ApplyConstraint(m_Position, m_Velocity);
	}
}
