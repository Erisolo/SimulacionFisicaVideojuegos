#include "SolidsSystem.h"

void SolidsSystem::addSolid()
{
	bool added = false; int i = 0;
	RigidSolid* p = generateSolid();


	while (!added && i < solids.size())
	{
		if (solids[i] == nullptr)
		{
			solids[i] = p;
			actNumOfSolids++;
			added = true;
		}
		i++;
	}
}

RigidSolid* SolidsSystem::generateSolid()
{
	Vector3 vel = meanVel; Vector3 pos = fuente;

	vel.x += normal_dist(seed) * velFac.x;
	vel.y += normal_dist(seed) * velFac.y;
	vel.z += normal_dist(seed) * velFac.z;

	pos.x += normal_dist(seed) * posFac.x;
	pos.y += normal_dist(seed) * posFac.y;
	pos.z += normal_dist(seed) * posFac.z;


	return new RigidSolid("cube", scene, gP, pos, vel, Vector4(0,1,0,1), Vector3(4), 5, 4);
}

void SolidsSystem::deleteDeadSolids()
{
	for (int i = 0; i < maxNumofSolids; i++)
	{
		if (solids[i] != nullptr && !solids[i]->alive())
		{
			delete solids[i];
			solids[i] = nullptr;
			actNumOfSolids--;
		}
	}
}

void SolidsSystem::deleteSolids()
{
	for (int i = 0; i < maxNumofSolids; i++)
	{
		if (solids[i] != nullptr)
		{
			delete solids[i];
			solids[i] = nullptr;
		}
	}
	actNumOfSolids = 0;
}


SolidsSystem::SolidsSystem(Vector3 initPos, PxScene* s, PxPhysics* g): scene(s), gP(g)
{
	fuente = initPos;
	seed = std::mt19937();
	normal_dist = std::normal_distribution<>(0, 1); //generar un número aleatorio entre -1 y 1;


	//asignamos constantes
	meanVel = { 0, -50, 0 };
	velFac = { 0, 5, 0 };
	posFac = { 15, 0, 15 };
	maxNumofSolids = 200;
	framerate = 0.1;




	solids = std::vector<RigidSolid*>(maxNumofSolids);
}

SolidsSystem::~SolidsSystem()
{
	deleteSolids();
}

void SolidsSystem::Update(double t)
{
	actTime += t;
	if (maxNumofSolids > actNumOfSolids && actTime > framerate)
	{
		addSolid();
		actTime = 0;
	}

	updateSolids(t);
	deleteDeadSolids();
}

void SolidsSystem::aplyForceGenerators(std::vector<ForceGenerator*>& fg)
{
}

void SolidsSystem::updateSolids(double t)
{
	for (int i = 0; i < solids.size(); i++)
	{
		if (solids[i] != nullptr)
		{
			solids[i]->update(t);
		}
	}
}
