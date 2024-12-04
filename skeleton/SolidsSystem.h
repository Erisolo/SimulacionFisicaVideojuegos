#pragma once
#include <vector>
#include <random>
#include "RigidSolid.h"
#include "ForceGenerator.h"
class SolidsSystem
{
protected:
	bool alive = true;
	std::vector<RigidSolid*> solids;
	int actNumOfSolids = 0;
	int maxNumofSolids;
	PxScene* scene;
	PxPhysics* gP;
	

private:
	Vector3 fuente;
	double framerate, actTime = 0;
	std::mt19937 seed;
	std::normal_distribution<> normal_dist;

	Vector3 meanVel, velFac, posFac;

	void addSolid();
	RigidSolid* generateSolid();
	void deleteDeadSolids();
	void deleteSolids();


public:
	SolidsSystem(Vector3 initPos, PxScene* s, PxPhysics* g);
	virtual ~SolidsSystem();

	virtual void Update(double t);

	virtual void aplyForceGenerators(std::vector<ForceGenerator*>& fg);
	void updateSolids(double t);
};

