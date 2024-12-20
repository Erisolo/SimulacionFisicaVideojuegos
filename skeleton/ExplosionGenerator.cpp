#include "ExplosionGenerator.h"

void ExplosionGenerator::aplyForce(Particle* p, double dt)
{
	Vector3 ppos = p->getPos();
	float r = (ppos - center).magnitudeSquared();

	if ( r < radiousSquared)
	{
		Vector3 force = (ppos - center) * (intesity / r) *exp(-time / tau);
		p->applyForce(force);
	}

}

void ExplosionGenerator::aplyForce(RigidSolid* p, double dt)
{
	Vector3 ppos = p->getPos();
	float r = (ppos - center).magnitudeSquared();

	if (r < radiousSquared)
	{
		Vector3 force = (ppos - center) * (intesity / r) * exp(-time / tau);
		p->applyForce(force);
	}
}

void ExplosionGenerator::Update(std::vector<Particle*>& ps, double dt)
{
	time += dt;
	ForceGenerator::Update(ps, dt);

	if (time > 4.6*tau) //cuando la sea menor q el 1%
		alive = false;
}
