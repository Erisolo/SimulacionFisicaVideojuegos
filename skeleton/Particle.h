#pragma once
#include <PxPhysicsAPI.h>
#include <ctype.h>
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;

class Particle
{

public:
	Particle(Vector3 pos, Vector3 vel);
	~Particle();

	void Integrate(double t);

private:
	Vector3 vel;
	PxTransform Pose;
	RenderItem* renderItem;
};

