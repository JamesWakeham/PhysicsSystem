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

}

void Plane::SetColour(glm::vec4 col)
{
	m_colour = col;
}
