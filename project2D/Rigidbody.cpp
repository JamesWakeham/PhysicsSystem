#include "Rigidbody.h"

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
	ApplyGravity( gravity * timeStep);
	applyForce(m_velocity * timeStep);
	LoopScreenCheck();
}

void Rigidbody::debug()
{
	
}

void Rigidbody::applyForce(glm::vec2 force)
{
	m_position += force;
}

void Rigidbody::applyForceToActor(Rigidbody * actor2, glm::vec2 force)
{

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
	m_position = pos;
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
