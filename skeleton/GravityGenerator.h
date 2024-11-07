#pragma once
#include "ForceGenerator.h"
class GravityGenerator: public ForceGenerator
{
private:
	Vector3 acceleration;

public:
	GravityGenerator(float accSpeed);
	void  aplyForce(Particle* p, double dt) override;
};

