#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"
#include <stdlib.h>     /* srand, rand */

PhysicsScene* PhysScenInstance;

PhysicsScene::PhysicsScene()
{
	PhysScenInstance = this;
}


PhysicsScene::~PhysicsScene()
{
	delete PhysScenInstance;
}

void PhysicsScene::Start()
{
	int i = rand();
	/* initialize random seed: */
	srand(GetApp()->getTime());
	i = rand();

	//AddActor(new Plane(500,glm::vec2(1,0),glm::vec4(1,0.75,0.5,1)));

	//AddActor(new Sphere(glm::vec2(100, 100), glm::vec2(100, 100), 1, 10, glm::vec4(1, 1, 1, 1)));

	for (int i = 0; i < 10; i++)
	{
		AddActor(
			new Sphere(
				glm::vec2(
					rand() % 900,
					rand() % 900),
				glm::vec2(
					rand() % 500,
					rand() % 500),
				1,
				20,
				glm::vec4(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f,1)));
	}
}


void PhysicsScene::update(float dt)
{
	for (int a = 0; a < m_actors.size(); a++)
	{
		m_actors[a]->fixedUpdate(m_gravity, dt);
		for (int b = a+1; b < m_actors.size(); b++)
		{
			Sphere2Sphere(m_actors[a], m_actors[b]);
			Sphere2Plane(m_actors[a], m_actors[b]);
		}
	}
}

void PhysicsScene::updateGizmos()
{
	for each (PhysicsObject* var in m_actors)
	{
		var->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{

}

bool PhysicsScene::SphereToSphereCollis(PhysicsObject * obj1, PhysicsObject * obj2)
{
	//try to cast objects to sphere and sphere 
	Sphere *sphere1 = dynamic_cast<Sphere*>(obj1); 
	Sphere *sphere2 = dynamic_cast<Sphere*>(obj2); 
	//if we are successful then test for collision 
	if (sphere1 != nullptr && sphere2 != nullptr) 
	{ 
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		float combinedSize = sphere1->getRadius() + sphere2->getRadius();

		if (distance < combinedSize)
		{
			//float m1 = sphere1->getMass();
			//float m2 = sphere2->getMass();
			//glm::vec2 v1 = sphere1->getVelocity();
			//glm::vec2 v2 = sphere2->getVelocity();
			glm::vec2 v1 = sphere1->getVelocity();
			//glm::vec2 v1f = ((m1 - m2) / (m1 + m2))*v1;
			//v1f += ((m2 * 2) / (m1 + m2))*v2;

			glm::vec2 v2 = sphere2->getVelocity();
			//glm::vec2 v2f = ((2*m1)/(m1+m2))*v1;
			//v2f -= ((m1-m2) / (m1+m2))*v2;

			float overlap = combinedSize - distance;
			sphere1->SetPos(sphere1->getPosition() + (glm::normalize(sphere1->getPosition() - sphere2->getPosition())*overlap));
			sphere2->SetPos(sphere2->getPosition() + (glm::normalize(sphere2->getPosition() - sphere1->getPosition())*overlap));
			
			float l1 = glm::length(v1);
			float l2 = glm::length(v2);
			float d = glm::dot(glm::normalize(v1), glm::normalize(v2));

			glm::vec2 v3 = v1*d;
			glm::vec2 v4 = v2*d;

			glm::vec2 v5 = v1 - v3;
			glm::vec2 v6 = v2 - v4;

			v1 = (v5 + v4);
			v2 = (v6 + v3);

			sphere1->applyForce(v1*2.0f);
			sphere2->applyForce(v2*2.0f);

			//sphere1->SetVelocity(glm::reflect(sphere1->getVelocity(), glm::normalize(sphere2->getPosition() - sphere1->getPosition())));
			//sphere2->SetVelocity(glm::reflect(sphere2->getVelocity(), glm::normalize(sphere2->getPosition() - sphere2->getPosition())));

		}
	}
	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject * obj1, PhysicsObject * obj2)
{
	//try to cast objects to sphere and sphere 
	Sphere *sphere1 = dynamic_cast<Sphere*>(obj1); 
	Sphere *sphere2 = dynamic_cast<Sphere*>(obj2); 
	//if we are successful then test for collision 
	if (sphere1 != nullptr && sphere2 != nullptr) 
	{ 
		glm::vec2 delta = sphere2->getPosition() - sphere1->getPosition(); 
		float distance = glm::length(delta);
		float intersection = sphere1->getRadius() + sphere2->getRadius() - distance; 
		if (intersection > 0) 
		{ 
			// respond to the collision 
			glm::vec2 collisionNormal = glm::normalize(delta); 
			glm::vec2 relativeVelocity = sphere1->getVelocity() - sphere2->getVelocity(); 
			glm::vec2 collisionVector = collisionNormal * (glm::dot(relativeVelocity, collisionNormal)); 
			glm::vec2 forceVector = collisionVector * 1.0f / (1.0f / sphere1->getMass() + 1.0f / sphere2->getMass());
			// use Newton's third law to apply collision forces 
			// to colliding bodies 
			sphere1->applyForceToActor(sphere2, forceVector); 
			// move out spheres out of collision 
			glm::vec2 separationVector = collisionNormal * intersection * 0.5f;
			sphere1->SetPos(sphere1->getPosition() - separationVector); 
			sphere2->SetPos(sphere2->getPosition() + separationVector);
			return true; 
		} 
	} 
	return false;
}

bool PhysicsScene::Sphere2Plane(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);
	if (sphere == nullptr || plane == nullptr) 
	{
		sphere = dynamic_cast<Sphere*>(obj2);
		plane = dynamic_cast<Plane*>(obj1);
	}
	//if we are successful then test for collision 
	if (sphere != nullptr && plane != nullptr) 
	{ 
		glm::vec2 collisionNormal = plane->GetNormal(); 
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->GetNormal()) - plane->GetDistance(); 
		//planes are infinitely thin, double sided objects so if 
		// we are behind it we flip the normal 
		if (sphereToPlane < 0) {
			collisionNormal *= -1; 
			sphereToPlane *= -1;
		}
		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0) 
		{ 
			// find the point where the collision occurred 
			// (we need this for collision response later) 
			// the plane is always static so collision response only 
			// applies to the sphere 
			glm::vec2 planeNormal = plane->GetNormal(); 
			if (sphereToPlane < 0) 
			{ 
				//flip the normal if we are behind the plane 
				planeNormal *= -1; 
			} 
			glm::vec2 forceVector = -1 * sphere->getMass() * planeNormal * (glm::dot(planeNormal, sphere->getVelocity()));
			sphere->applyForce(2.0f * forceVector);
			sphere->SetPos(sphere->getPosition() + collisionNormal * intersection * 0.5f); 
			return true; 
		} 
	}
	return false;
}

void PhysicsScene::AddActor(PhysicsObject* obj)
{
	m_actors.push_back(obj);
}

void PhysicsScene::RemoveActor(PhysicsObject* obj)
{
	
	//m_actors.remove(obj);
}
