#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator: public ForceGenerator
{
private:

	Particle* startPoint;
	double K, rest_len;

public:
	SpringForceGenerator(Particle* sp, double k, double rl): startPoint(sp), K(k), rest_len(rl) {};
	void aplyForce(Particle* p, double dt) override;
	Particle* getStartPoint() { return startPoint;};
	void changeStartPoint(Particle* p) { startPoint = p; }

	void changeK(float nk) { K = nk; };
};

