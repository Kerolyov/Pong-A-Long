#ifndef Sprite_h__
#define Sprite_h__
#pragma once

#include <sdl.h>

class Sprite
{
public:
	friend class Texture;
	enum AnchorPt { TOPLEFT, TOPCENTRE, TOPRIGHT, LEFT, CENTRE, RIGHT, LOWLEFT, LOWCENTRE, LOWRIGHT, CUSTOM };

	Sprite() {}
	virtual ~Sprite() {}

	int GetXOffset() const;
	int GetYOffset() const;
	SDL_Rect GetDestRect() const;

	void SetClipRect(SDL_Rect rect) { m_ClipRect = rect; }

	int GetTextureID() const { return m_TextureID; }
	void SetTextureID(int id) { m_TextureID = id; }

	void SetAnchorPt(AnchorPt anchor) { m_AnchorPt = anchor; }

	void SetRotation(double angle_rad) { m_rotation_angle = angle_rad; }

	void SetFlip(SDL_RendererFlip flip) { m_Flip = flip; }

protected:
	int m_TextureID = -1;

	AnchorPt m_AnchorPt = CENTRE;

	SDL_Rect m_ClipRect = { 0, 0, 0, 0 };

	double m_rotation_angle = 0.0;
	SDL_Point m_RotationCentre = {0,0};

	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
};

#endif // Sprite_h__

