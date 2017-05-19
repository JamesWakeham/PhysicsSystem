#pragma once
#include "PhysicsObject.h"
#include "Application2D.h"

class Rigidbody : public PhysicsObject 
{
public:
	Rigidbody() = default;
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~Rigidbody(); 
	
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep); 
	virtual void debug(); 
	void applyForce(glm::vec2 force); 
	void applyForceToActor(Rigidbody* actor2, glm::vec2 force); 
	glm::vec2 getPosition() { return m_position; } 
	
	void ApplyGravity(glm::vec2 gravityDelta);

	float getRotation() { return m_rotation; } 
	glm::vec2 getVelocity() { return m_velocity; }
	void SetVelocity(glm::vec2 vel);
	void SetPos(glm::vec2 pos);
	float getMass() { return m_mass; } 

	void LoopScreenCheck();
protected: 
	glm::vec2 m_position; 
	glm::vec2 m_velocity; 
	float m_mass; 
	float m_rotation; 
		   //2D so we only need a single float to represent our rotation 
};
