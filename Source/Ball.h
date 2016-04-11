#ifndef Ball_h__
#define Ball_h__
#pragma once

class Window;
#include "GameObject.h"

class Ball : public GameObject
{
public:
	friend class PongApp;

	Ball();
	virtual ~Ball();

	void Reset(Window& window);
	
private:
	double m_Speed = 200.;
};

#endif // Ball_h__

