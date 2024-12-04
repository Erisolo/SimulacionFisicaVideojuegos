#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::aplyForce(Particle* p, double dt)
{
	float h = p->getPos().y;
	float h0 = waterline->getPos().y;
	Vector3 force = Vector3(0.0);


	float immersed = 0.0;

	if ((h - h0) > height * 0.5) {
		immersed = 0.0;
	}

	else if ((h0 - h) > height * 0.5) {
		immersed = 1.0;
	}

	else {
		immersed = (h0 - h) / height + 0.5;
	}

	force.y = density * volume * immersed; // *9.8;
	p->applyForce(force);

}
