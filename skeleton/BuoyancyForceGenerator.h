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
	BuoyancyForceGenerator(Particle* sp, double k, double rl, bool ssp = true, bool nlf = true);
	void Update(std::vector<Particle*>& ps, double dt = 0) override;
	void aplyForce(Particle* p, double dt) override;
};

