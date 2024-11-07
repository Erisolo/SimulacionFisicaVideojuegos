#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3 vel, float Wi, Vector3 cntr, float roi) : ForceGenerator(), windResistence(Wi), windSpeed(vel), center(cntr)
{
	radiousOfInfluenceSquared = pow(roi, 2);
}

void WindGenerator::aplyForce(Particle* p, double dt)
{
	if ((p->getPos() - center).magnitudeSquared() < radiousOfInfluenceSquared)
	{
		Vector3 force = windResistence * (windSpeed - p->getVel());
		p->applyForce(force);

	}
}
