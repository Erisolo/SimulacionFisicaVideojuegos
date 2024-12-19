#pragma once
//#include "Particle.h"
#include "ParticleSystem.h"
#include "ForceGenerator.h"
#include "SolidsSystem.h"
#include <PxPhysicsAPI.h>

using namespace physx;
class Spring;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void Uptade(double t);
	void Shoot(char c, Vector3 pos);

	void addNecesitiesForRigids(PxScene* s, PxPhysics* gP) noexcept { scene = s; gPhysics = gP; }
	void onColision(physx::PxActor* actor1, physx::PxActor* actor2);

	void gameWon();


private:
	std::vector<Particle*> particles;
	std::vector<ParticleSystem*> sistemaParticulas;
	std::vector<ForceGenerator*> forceGenerators;
	std::vector<RigidSolid*> solids;
	std::vector<SolidsSystem*> solidSystems;

	PxScene* scene;
	PxPhysics* gPhysics;

	//now onto my pretty little player
	RigidSolid* player;
	PxRigidStatic* suelo;
	SolidsSystem* obstacleGenerator;
	bool gameOver = false;

	void lostGame();
};

