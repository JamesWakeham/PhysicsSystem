#include "SpringJoint.h"

SpringJoint::SpringJoint(Rigidbody * connection1, Rigidbody * connection2, float springCoefficient, float damping)
{
	rb1 = connection1;
	rb2 = connection2;
	m_springCoefficient = springCoefficient;
	m_damping = damping;
	m_restLength = glm::length(rb1->getPosition() - rb2->getPosition());
}

void SpringJoint::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	float displacement = m_restLength - glm::length(rb1->getPosition()- rb2->getPosition());
	float F = -m_springCoefficient*displacement;
	F = F - (m_damping*F);
	rb1->applyForceToActor(rb2, (rb1->getPosition() - rb2->getPosition())*F);
}

void SpringJoint::debug()
{

}

void SpringJoint::makeGizmo()
{
	GetApp()->GetRenderer()->setRenderColour(0.75f, 0.75f, 0.75f, 1);
	GetApp()->GetRenderer()->drawLine(rb1->getPosition().x, rb1->getPosition().y, rb2->getPosition().x, rb2->getPosition().y, 2, 0);
}
