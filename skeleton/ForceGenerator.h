#pragma once
#include "Particle.h"
class SceneManager;
class ForceGenerator
{
protected:
	int id;
	SceneManager* mngr;

public:

	ForceGenerator(int i, SceneManager* sm): id(i), mngr(sm) {};
	virtual void aplyForce(Particle* p, double dt) = 0;
	virtual void Update(std::vector<Particle*> ps, double dt) = 0;
	virtual void stop();

};

