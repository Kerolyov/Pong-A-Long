#include "Sprite.h"


SDL_Rect Sprite::GetDestRect() const
{
	return{ m_AnchorPt.x, m_AnchorPt.y, m_ClipRect.w, m_ClipRect.h };
}

void Sprite::SetClipRect(SDL_Rect rect)
{
	m_ClipRect = rect;
}

void Sprite::SetAnchorPt(AnchorPt anchor)
{
	if (anchor == CENTRE || anchor == TOPCENTRE || anchor == LOWCENTRE)
		m_AnchorPt.x = -m_ClipRect.w / 2;
	else if (anchor == RIGHT || anchor == TOPRIGHT || anchor == LOWRIGHT)
		m_AnchorPt.x = -m_ClipRect.w;
	else
		m_AnchorPt.x = 0;

	if (anchor == LEFT || anchor == CENTRE || anchor == RIGHT)
		m_AnchorPt.y = -m_ClipRect.h / 2;
	else if (anchor == LOWLEFT || anchor == LOWCENTRE || anchor == LOWRIGHT)
		m_AnchorPt.y = -m_ClipRect.h;
	else
		m_AnchorPt.y = 0;
}

