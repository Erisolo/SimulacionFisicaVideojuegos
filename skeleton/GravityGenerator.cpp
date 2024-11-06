#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(float accSpeed): ForceGenerator()
{

	acceleration = { 0, -accSpeed, 0};
}

void GravityGenerator::aplyForce(Particle* p)
{
	Vector3 force = p->getMass() * acceleration;
	p->applyForce(force);
}
