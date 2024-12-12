#pragma once
#include <vector>
#include <random>
#include "RigidSolid.h"
#include "ForceGenerator.h"


enum GenerationSystems;
class SolidsSystem
{
protected:
	bool alive = true;
	std::vector<RigidSolid*> solids;
	int actNumOfSolids = 0;
	int maxNumofSolids = 0;
	PxScene* scene;
	PxPhysics* gP;
	bool constantGen = true;
	Vector3 fuente;
	double framerate, actTime = 0;
	std::mt19937 seed;
	std::normal_distribution<> normal_dist;
	float lifeTime;
	void deleteDeadSolids();

private:
	

	Vector3 meanVel, velFac, posFac;

	void addSolid();
	RigidSolid* generateSolid();
	
	void deleteSolids();
	void asignateSystem(GenerationSystems g);

	void initSystem();


public:
	SolidsSystem(Vector3 initPos, PxScene* s, PxPhysics* g, GenerationSystems gs);
	virtual ~SolidsSystem();

	virtual void Update(double t);

	virtual void aplyForceGenerators(std::vector<ForceGenerator*>& fg);
	void updateSolids(double t);
};

