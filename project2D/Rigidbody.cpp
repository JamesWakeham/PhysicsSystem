#include "Rigidbody.h"
#include <cfloat>


Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	if (!isStatic) 
	{
		ApplyGravity(gravity * timeStep);
		m_position += m_velocity *timeStep;
		m_velocity = m_velocity * m_friction;
		LoopScreenCheck();
	}
}

void Rigidbody::debug()
{
	
}

void Rigidbody::applyForce(glm::vec2 force)
{
	m_velocity = (m_velocity)+(force/m_mass);
}

void Rigidbody::applyForceToActor(Rigidbody * actor2, glm::vec2 force)
{
	applyForce(-force);
	actor2->applyForce(force);
}

void Rigidbody::ApplyGravity(glm::vec2 gravityDelta)
{
	m_velocity += gravityDelta;
}

void Rigidbody::SetVelocity(glm::vec2 vel)
{
	m_velocity = vel;
}

void Rigidbody::SetPos(glm::vec2 pos)
{
	if (!isStatic)
		m_position = pos;
}

float Rigidbody::getMass()
{
	if (isStatic) {
		return FLT_MAX;
	}else
	return m_mass;
	
}

void Rigidbody::LoopScreenCheck()
{
	if (m_position.x > GetApp()->getWindowWidth())
	{
		m_position.x = 0;
	} else if(m_position.x < 0) {
		m_position.x = GetApp()->getWindowWidth();
	}

	if (m_position.y > GetApp()->getWindowHeight())
	{
		m_position.y = 0;
	}
	else if (m_position.y < 0) {
		m_position.y = GetApp()->getWindowHeight();
	}
}

void Rigidbody::SetFriction(float _friction)
{
	m_friction = _friction;
}
