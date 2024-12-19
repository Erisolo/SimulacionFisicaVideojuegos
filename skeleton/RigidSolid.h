#pragma once
#include <PxPhysicsAPI.h>
#include <string>
#include "core.hpp"
#include <ctype.h>
#include "RenderUtils.hpp"

using namespace physx;
class RigidSolid
{
private:
	bool isAlive = true;
	PxRigidDynamic* body;
	PxTransform trans;
	RenderItem* renderItem;
	float lifeTime;


public:
	RigidSolid(std::string shape, PxScene* s, PxPhysics* gP, Vector3 pos, Vector3 vel, Vector4 col, Vector3 size, float mass, float lf = 0, bool lockin = false, bool lockedotherway = false);
	~RigidSolid();

	//void Integrate(double t);
	inline bool alive() noexcept { return isAlive; }
	void update(double dt);
	void applyForce(Vector3 fc);
	void setSpeed(Vector3 s);
	Vector3 getPos();
	Vector3 getVel();
	PxRigidDynamic* getActor() { return body; }

	void setPosXZ(Vector3 pos);


};

