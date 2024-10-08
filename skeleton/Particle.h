#pragma once
#include <PxPhysicsAPI.h>
#include <ctype.h>
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;

class Particle
{

public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double d);
	~Particle();

	virtual void Integrate(double t);
	void ChangeAcceleration(Vector3 acc);
	bool hasTouchedGround() { return Pose.p.y <= 0; }
	void changeColor(Vector4 color) { renderItem->color = color; }

protected:
	Vector3 vel;
	Vector3 acc;
	double damping;
	PxTransform Pose;
	RenderItem* renderItem;
};

