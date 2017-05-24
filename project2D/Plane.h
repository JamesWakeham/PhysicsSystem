#pragma once
#include "Rigidbody.h"
class Plane :
	public Rigidbody
{
public:
	Plane(float _m_distance, glm::vec2 _m_normal, glm::vec4 _col) { m_distance = _m_distance; m_normal = _m_normal; m_colour = _col; m_shapeID = ShapeType::PLANE; };
	~Plane();

	// these should be protected but ill fix that if anyone else works with the code.
	glm::vec2 m_normal;
	float m_distance;

	float GetDistance();
	glm::vec2 GetNormal();

	virtual void makeGizmo();
	glm::vec4 getColour() { return m_colour; }
	void SetColour(glm::vec4 col);
protected:
	glm::vec4 m_colour;
};

