#include "Sprite.h"

int Sprite::GetXOffset() const
{
	if (m_AnchorPt == CENTRE || m_AnchorPt == TOPCENTRE || m_AnchorPt == LOWCENTRE)
		return - m_ClipRect.w / 2;

	if (m_AnchorPt == RIGHT || m_AnchorPt == TOPRIGHT || m_AnchorPt == LOWRIGHT)
		return  - m_ClipRect.w;

	return 0;
}

int Sprite::GetYOffset() const
{
	if (m_AnchorPt == LEFT || m_AnchorPt == CENTRE || m_AnchorPt == RIGHT)
		return - m_ClipRect.h / 2;

	if (m_AnchorPt == LOWLEFT || m_AnchorPt == LOWCENTRE || m_AnchorPt == LOWRIGHT)
		return - m_ClipRect.h;

	return 0;
}

SDL_Rect Sprite::GetDestRect() const
{
	return{ GetXOffset(), GetYOffset(), m_ClipRect.w, m_ClipRect.h };
}


