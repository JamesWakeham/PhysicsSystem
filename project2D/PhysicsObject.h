#pragma once
#include <glm\glm.hpp>

enum ShapeType 
{ 
	PLANE = 0, 
	SPHERE = 1, 
	BOX = 2, 
}; 

class PhysicsObject 
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
	ShapeType m_shapeID;
public:
	PhysicsObject() = default;
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0; 
	virtual void debug() = 0; 
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
};
