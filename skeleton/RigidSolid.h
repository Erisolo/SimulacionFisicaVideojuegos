#pragma once
#include <PxPhysicsAPI.h>
class RigidSolid
{
private:
	bool isAlive;
	PxRigidDynamic* body;


public:
	RigidSolid(std::string shape, PxScene* s, PxPhysics* gP, Vector3 pos, Vector3 vel);

	//void Integrate(double t);
	inline bool alive() { return isAlive; }
	void applyForce(Vector3 fc);


};

