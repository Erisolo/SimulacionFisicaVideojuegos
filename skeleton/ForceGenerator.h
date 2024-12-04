#pragma once
#include "Particle.h"
#include "RigidSolid.h"
class SceneManager;
class ForceGenerator
{
protected:
	bool alive = true;

public:

	ForceGenerator() {};
	virtual void aplyForce(Particle* p, double dt) = 0;
	virtual void aplyForce(RigidSolid* p, double dt = 0) {}
	virtual void Update(std::vector<Particle*> &ps, double dt = 0);
	virtual void Update(std::vector<RigidSolid*>& ps, double dt = 0);

	bool isAlive() { return alive; }

	
};

