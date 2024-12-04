#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator: public ForceGenerator
{
private:

	Particle* startPoint;
	double K, rest_len;
	bool staticSP;
	bool negativeLenghtForce;

public:
	SpringForceGenerator(Particle* sp, double k, double rl, bool ssp = true, bool nlf = true): startPoint(sp), K(k), rest_len(rl), staticSP(ssp), negativeLenghtForce(nlf) {};
	void Update(std::vector<Particle*>& ps, double dt = 0) override;
	void aplyForce(Particle* p, double dt) override;
	Particle* getStartPoint() { return startPoint;};
	void changeStartPoint(Particle* p) { startPoint = p; }

	void changeK(float nk) { K = nk; };
};

