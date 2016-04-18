#ifndef Constraint_h__
#define Constraint_h__
#pragma once

class Constraint
{
public:
	enum Axis { AXIS_X, AXIS_Y};
	Constraint() {}
	virtual ~Constraint() {}

	virtual void ApplyConstraint(Vec2D& position, Vec2D& velocity) = 0;
private:
};

class ClampMax : public Constraint
{
public:
	ClampMax(Axis axis, double max) : m_axis(axis), m_Max(max) {}
	~ClampMax() {}

	void ApplyConstraint(Vec2D& position, Vec2D& velocity)
	{
		double& value = (m_axis == AXIS_X) ? position.x : position.y; 

		if (value > m_Max)
			value = m_Max;
	}

protected:
	Axis	m_axis;
	double m_Max = 0.0;
};

class ClampMin : public Constraint
{
public:
	ClampMin(Axis axis, double min) : m_axis(axis), m_Min(min) {}
	~ClampMin() {}

	void ApplyConstraint(Vec2D& position, Vec2D& velocity)
	{
		double& value = (m_axis == AXIS_X) ? position.x : position.y;

		if (value < m_Min)
			value = m_Min;
	}

protected:
	Axis	m_axis;
	double m_Min = 0.0;
};

class LoopAround : public Constraint
{
public:
	LoopAround(Axis axis, double min, double max, double offset) : m_axis(axis), m_Min(min), m_Max(max), m_Offset(offset) {}
	~LoopAround() {}

	void ApplyConstraint(Vec2D& position, Vec2D& velocity)
	{
		double& value = (m_axis == AXIS_X) ? position.x : position.y;

		if (value < m_Min)
			value = m_Max + m_Offset;

		if (value > m_Max)
			value = m_Min - m_Offset;
	}

protected:
	Axis	m_axis;
	double m_Min = 0.0;
	double m_Max = 0.0;
	double m_Offset = 0.0;
};

#endif // Constraint_h__

