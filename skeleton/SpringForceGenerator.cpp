#include "SpringForceGenerator.h"

void SpringForceGenerator::Update(std::vector<Particle*>& ps, double dt)
{
	if (!staticSP)
	{
		//todas las particulas van a tener la misma pos
		Vector3 RelativePos = ps[0]->getPos() - startPoint->getPos();

		float len = RelativePos.normalize();
		float delta = len - rest_len;

		if (negativeLenghtForce || delta >= 0)
		{
			startPoint->applyForce(RelativePos * delta * K);
		}

		
		//esto es como el aply force pero al reves
	}

	ForceGenerator::Update(ps, dt);
}
void SpringForceGenerator::Update(std::vector<RigidSolid*>& ps, double dt)
{
	if (!staticSP)
	{
		//todas las particulas van a tener la misma pos
		Vector3 RelativePos = ps[0]->getPos() - startPoint->getPos();

		float len = RelativePos.normalize();
		float delta = len - rest_len;

		if (negativeLenghtForce || delta >= 0)
		{
			startPoint->applyForce(RelativePos * delta * K);
		}


		//esto es como el aply force pero al reves
	}

	ForceGenerator::Update(ps, dt);
}

void SpringForceGenerator::aplyForce(Particle* p, double dt)
{
	Vector3 RelativePos = startPoint->getPos() - p->getPos();

	float len = RelativePos.normalize();
	float delta = len - rest_len;

	if (negativeLenghtForce || delta >= 0)
	{
		p->applyForce(RelativePos * delta * K);
	}
}
void SpringForceGenerator::aplyForce(RigidSolid* p, double dt)
{
	Vector3 RelativePos = startPoint->getPos() - p->getPos();

	float len = RelativePos.normalize();
	float delta = len - rest_len;

	if (negativeLenghtForce || delta >= 0)
	{
		p->applyForce(RelativePos * delta * K);
	}
}
