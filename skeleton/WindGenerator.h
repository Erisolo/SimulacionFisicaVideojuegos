#pragma once
#include "ForceGenerator.h"
class WindGenerator: public ForceGenerator
{
private:
	Vector3 center; float radiousOfInfluenceSquared;
	Vector3 windSpeed;
	float windResistence;

public:

	WindGenerator(Vector3 vel, float Wi, Vector3 cntr, float roi);
	void aplyForce(Particle* p) override;

};

