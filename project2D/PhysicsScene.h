#pragma once
#include "PhysicsObject.h"
#include <vector>

class PhysicsScene 
{ 
public: 
	PhysicsScene(); 
	~PhysicsScene();

	void Start();

	void update(float dt); 
	void updateGizmos(); 
	void debugScene(); 
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; } 
	
	glm::vec2 getGravity() const { return m_gravity; } 
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; } 
	float getTimeStep() const { return m_timeStep; } 

	bool SphereToSphereCollis(PhysicsObject* obj1, PhysicsObject* obj2);

	void AddActor(PhysicsObject* obj);
	void RemoveActor(PhysicsObject* obj);
protected: 
	glm::vec2 m_gravity = glm::vec2(0,0);
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};
