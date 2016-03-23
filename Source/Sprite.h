#ifndef Sprite_h__
#define Sprite_h__
#pragma once

#include <sdl.h>
#include <memory>

class Sprite
{
public:
	friend class Texture;
	enum AnchorPt { TOPLEFT, TOPCENTRE, TOPRIGHT, LEFT, CENTRE, RIGHT, LOWLEFT, LOWCENTRE, LOWRIGHT, CUSTOM };

	Sprite() {}
	virtual ~Sprite() {}

	SDL_Rect GetDestRect() const;

	int GetTextureID() const { return m_TextureID; }


	void SetTextureID(int id) { m_TextureID = id; }

	void SetClipRect(SDL_Rect rect);

	void SetAnchorPt(AnchorPt anchor);
	void SetAnchorPt(SDL_Point anchorpt) { m_AnchorPt = anchorpt; }

	void SetRotation(double angle_rad) { m_rotation_angle = angle_rad; }

	void SetFlip(SDL_RendererFlip flip) { m_Flip = flip; }

protected:
	int m_TextureID = -1;

	SDL_Point m_AnchorPt = { 0, 0 };

	SDL_Rect m_ClipRect = { 0, 0, 0, 0 };

	double m_rotation_angle = 0.0;
	std::unique_ptr<SDL_Point> m_pRotationCentre = nullptr;

	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
};

#endif // Sprite_h__

