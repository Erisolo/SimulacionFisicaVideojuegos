#include "SpringForceGenerator.h"

void SpringForceGenerator::aplyForce(Particle* p, double dt)
{
	Vector3 RelativePos = startPoint->getPos() - p->getPos();

	float len = RelativePos.normalize();
	float delta = len - rest_len;

	p->applyForce(RelativePos * delta * K);
}
