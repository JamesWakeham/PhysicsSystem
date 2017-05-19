#pragma once
#include "Rigidbody.h"
#include <Gizmos.h>

class Sphere : public Rigidbody 
{ 
public:
	Sphere() = default;
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	~Sphere(); 
	virtual void makeGizmo(); 
	float getRadius() { return m_radius; } 
	glm::vec4 getColour() { return m_colour; } 
	void SetColour(glm::vec4 col);
protected: 
	float m_radius; 
	glm::vec4 m_colour; 
};
