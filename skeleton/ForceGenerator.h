#pragma once
#include "Particle.h"
class SceneManager;
class ForceGenerator
{
protected:
	bool alive = true;

public:

	ForceGenerator() {};
	virtual void aplyForce(Particle* p, double dt) = 0;
	virtual void Update(std::vector<Particle*> &ps, double dt);

};

