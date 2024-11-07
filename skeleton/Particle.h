#pragma once
#include <PxPhysicsAPI.h>
#include <ctype.h>
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;

class Particle
{

public:
	Particle(Vector3 pos, Vector3 vel, float m);
	Particle(Vector3 pos, Vector3 vel, double lf, Vector4 col, float m);
	~Particle();

	virtual void Integrate(double t);
	void ChangeAcceleration(Vector3 acc);
	bool hasTouchedGround() { return Pose.p.y <= 0; }
	void changeColor(Vector4 color) { renderItem->color = color; }

	inline bool alive() { return isAlive; }
	void applyForce(Vector3 fc);
	Vector3 getVel() { return vel; }
	double getMass() { return myMass; }
	Vector3 getPos() { return Pose.p; }

protected:
	Vector3 vel;
	Vector3 acc;
	Vector3 forces;
	float myMass;
	//double damping;
	PxTransform Pose;
	RenderItem* renderItem;
	bool isAlive = true;
	double lifeTime;
};

