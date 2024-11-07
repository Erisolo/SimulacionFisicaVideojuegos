#include "ExplosionGenerator.h"

void ExplosionGenerator::aplyForce(Particle* p, double dt)
{
	Vector3 ppos = p->getPos();
	float r = (ppos - center).magnitudeSquared();

	if ( r < radiousSquared)
	{
		Vector3 force = (ppos - center) * (intesity / r) * exp(-dt/tau);
	}

}
