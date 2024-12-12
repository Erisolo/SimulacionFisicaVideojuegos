#pragma once
#include "SolidsSystem.h"
#include "ParticleSystem.h"
class ObstaclesGenerator: public SolidsSystem
{
private:
	std::vector<ParticleSystem*> particleSystems;
	Vector3 vel;
	Vector3 sizeOfPath;
	Vector4 color = { 0.9, 0.6, 0.3, 1.0};

public:
	ObstaclesGenerator(PxScene* s, PxPhysics* g, Vector3 pos, Vector3 vel, Vector3 acc, Vector3 size, float lf);
	~ObstaclesGenerator();
	void generateNextObstacle();
	void Update(double dt) override;

private:
	void makeFloor();

};

