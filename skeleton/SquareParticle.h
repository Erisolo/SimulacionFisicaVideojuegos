#pragma once
#include "Particle.h"
class SquareParticle: public Particle
{
public:
	SquareParticle(Vector3 pos, Vector3 vel, float m, float w, float h, float d);
	SquareParticle(Vector3 pos, Vector3 vel, double lf, Vector4 col, float m, float w, float h, float d);

	void init() override;
private:
	float height, width, depth;
};

