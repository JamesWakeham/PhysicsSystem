#include "Sphere.h"
#include "Application2D.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{

}

void Sphere::makeGizmo()
{
	GetApp()->GetRenderer()->setRenderColour(m_colour.r, m_colour.g, m_colour.b, m_colour.a);
	GetApp()->GetRenderer()->drawCircle(m_position.x, m_position.y, m_radius, 0);
}

void Sphere::SetColour(glm::vec4 col)
{
	m_colour = col;
}
