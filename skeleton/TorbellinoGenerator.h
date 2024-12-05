#pragma once
#include "WindGenerator.h"
class TorbellinoGenerator: public WindGenerator
{
private:
	float huracaneIntensity;
public:
	TorbellinoGenerator(float Wi, Vector3 cntr, float roi, float hi);
	void aplyForce(Particle* p, double dt) override;
	void aplyForce(RigidSolid* p, double dt) override;

};

