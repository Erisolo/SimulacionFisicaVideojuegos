#pragma once
#include "Particle.h"
class ForceGenerator
{
protected:


public:

	ForceGenerator() {};
	virtual void aplyForce(Particle* p) = 0;

};

