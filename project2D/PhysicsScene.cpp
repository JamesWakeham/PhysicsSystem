#include "PhysicsScene.h"
#include "Sphere.h"
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

	AddActor(
		new Sphere(
			glm::vec2(
				rand() % 900,
				rand() % 900),
			glm::vec2(
				rand() % 1000,
				rand() % 1000),
			1,
			20,
			glm::vec4(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f, 1)));

	for (int i = 0; i < 25; i++)
	{
		AddActor(
			new Sphere(
				glm::vec2(
					rand() % 900,
					rand() % 900),
				glm::vec2(
					rand() % 100,
					rand() % 100),
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
			SphereToSphereCollis(m_actors[a], m_actors[b]);
		}
	}
	//for each (PhysicsObject* obj1 in m_actors)
	//{
	//	obj1->fixedUpdate(m_gravity, dt);
	//	for each (PhysicsObject* obj2 in m_actors)
	//	{
	//		if (obj1 != obj2)
	//			SphereToSphereCollis(obj1,obj2);
	//	}
	//}
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
			float m1 = sphere1->getMass();
			float m2 = sphere2->getMass();
			glm::vec2 v1 = sphere1->getVelocity();
			glm::vec2 v2 = sphere2->getVelocity();

			glm::vec2 v1f = ((m1 - m2) / (m1 + m2))*v1;
			v1f += ((m2 * 2) / (m1 + m2))*v2;

			glm::vec2 v2f = ((2*m1)/(m1+m2))*v1;
			v2f -= ((m1-m2) / (m1+m2))*v2;

			float overlap = combinedSize - distance;
			sphere1->SetPos(sphere1->getPosition() + (glm::normalize(sphere1->getPosition() - sphere2->getPosition())*overlap));
			sphere2->SetPos(sphere2->getPosition() + (glm::normalize(sphere2->getPosition() - sphere1->getPosition())*overlap));
			
			sphere1->SetVelocity(v1f);
			sphere2->SetVelocity(v2f);

			//sphere1->SetVelocity(glm::reflect(sphere1->getVelocity(), glm::normalize(sphere2->getPosition() - sphere1->getPosition())));
			//sphere2->SetVelocity(glm::reflect(sphere2->getVelocity(), glm::normalize(sphere2->getPosition() - sphere2->getPosition())));

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
