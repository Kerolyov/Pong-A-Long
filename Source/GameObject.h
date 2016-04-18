#ifndef GameObject_h__
#define GameObject_h__
#pragma once

#include <vector>
#include <memory>
#include <SDL.h>

#include "Vec2D.h"
#include "sprite.h"

#include "Constraint.h"


class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	void InitialiseSprite(int id, SDL_Rect size_rect, Sprite::AnchorPt anchorpt = Sprite::CENTRE );

	void AddConstraint(std::unique_ptr<Constraint> pConstraint) { m_Constraints.push_back(std::move(pConstraint)); }

	void SetClipRect(SDL_Rect rect) { m_Sprite.SetClipRect(rect); }
	void SetPosition(Vec2D pos) { m_Position = pos; }
	void SetVelocity(Vec2D vel) { m_Velocity = vel; }

	SDL_Rect GetSpriteRect() const;
	const Sprite& GetSprite() const { return m_Sprite; }

	Sprite& GetSprite() { return m_Sprite; }
	
	const Vec2D& GetVel() const { return m_Velocity; }
	const Vec2D& GetPos() const { return m_Position; }

	virtual void Update(double dt);

protected:
	Vec2D m_Position;
	Vec2D m_Velocity;

	std::vector<std::unique_ptr<Constraint>> m_Constraints;

	Sprite m_Sprite;
};

#endif GameObject_h__

