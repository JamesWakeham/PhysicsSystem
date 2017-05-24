#include "Plane.h"

Plane::~Plane()
{
}

float Plane::GetDistance()
{
	return m_distance;
}

glm::vec2 Plane::GetNormal()
{
	return m_normal;
}

void Plane::makeGizmo()
{
	GetApp()->GetRenderer()->setRenderColour(m_colour.r, m_colour.g, m_colour.b, m_colour.a);
	GetApp()->GetRenderer()->drawLine(-m_normal.x*m_distance, 1000, -m_normal.x*m_distance, 0, 2, 0);
}

void Plane::SetColour(glm::vec4 col)
{
	m_colour = col;
}
