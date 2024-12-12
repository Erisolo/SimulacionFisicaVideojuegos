#pragma once
#include "Particle.h"
#include <vector>
#include <random>

class ForceGenerator;

enum GenerationSystems
{
	RAIN, EXPLOSION, FIREWORKS, MANGUERA, NONE
};
class ParticleSystem
{
protected:
	bool alive = true;
	std::vector<Particle*> particles;
	int actNumOfParts = 0;
	int maxNumofParts;
	void deleteDeadParticles();
	void deleteParticles();

	void updateParticles(double t);


private:
	
	Vector3 fuente;
	double lifeTime;
	double framerate, actTime = 0;
	std::mt19937 seed;
	bool constantGen;
	std::normal_distribution<> normal_dist;

	Vector3 meanVel, velFac, posFac;

	void addParticle();
	Particle* generateParticle();
	void asignateSystem(GenerationSystems g);
	void initSystem(GenerationSystems g);

public:
	ParticleSystem(Vector3 initPos, GenerationSystems g);
	ParticleSystem() {};
	virtual ~ParticleSystem();

	virtual void Update(double t);

	virtual void aplyForceGenerators(std::vector<ForceGenerator*>& fg);
};

