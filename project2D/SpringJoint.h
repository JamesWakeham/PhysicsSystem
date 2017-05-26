#pragma once
#include "PhysicsObject.h"
#include "Rigidbody.h"
class SpringJoint :
	public PhysicsObject
{
public: 
	SpringJoint(Rigidbody* connection1, Rigidbody* connection2, float springCoefficient, float damping); 
private: 
	void virtual fixedUpdate(glm::vec2 gravity, float timeStep); 
	void virtual debug(); 
	void virtual makeGizmo(); 
	Rigidbody* rb1;
	Rigidbody* rb2;
	float m_damping; 
	float m_restLength; 
	float m_springCoefficient;
};

