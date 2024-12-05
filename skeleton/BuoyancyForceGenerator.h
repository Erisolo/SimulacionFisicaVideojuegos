#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator: public ForceGenerator
{
private:

	Particle* waterline;
	float height;
	float volume;
	float density;

public:
	BuoyancyForceGenerator(Particle* wt, float h, float d, float v): waterline(wt), height(h), density(d), volume(v){}
	void aplyForce(Particle* p, double dt = 0) override;
	void aplyForce(RigidSolid* p, double dt = 0) override;

	void changeObjectProperties(float h, float v) { height = h; volume = v; }
};

