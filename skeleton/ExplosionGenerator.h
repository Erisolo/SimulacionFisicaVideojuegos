#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator: public ForceGenerator
{
private:
	Vector3 center;
	float intesity;
	float radiousSquared;
	float tau;
	double time = 0;


public:

	ExplosionGenerator(SceneManager* mn, int id, Vector3 c, float i, float r, float t = 4) : ForceGenerator(id, mn), center(c), intesity(i), radiousSquared(pow(r, 2)), tau(t) {};
	void  aplyForce(Particle* p, double dt) override;
	void Update(std::vector<Particle*> ps, double dt) override;

};

