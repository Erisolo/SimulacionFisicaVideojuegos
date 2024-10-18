#pragma once
#include "Particle.h"
#include <vector>
#include <random>

enum GenerationSystems
{
	RAIN, EXPLOSION, FIREWORKS, MANGUERA
};
class ParticleSystem
{
private:
	Vector3 fuente;
	std::vector<Particle*> particles;
	int actNumOfParts = 0;
	int maxNumofParts;
	double lifeTime;
	double framerate, actTime = 0;
	std::mt19937 seed;
	bool constantGen;
	std::normal_distribution<> normal_dist;

	Vector3 meanVel, velFac, posFac;


	void deleteParticles();
	void deleteDeadParticles();
	void addParticle();
	void updateParticles(double t);
	Particle* generateParticle();
	void asignateSystem(GenerationSystems g);
	void initSystem(GenerationSystems g);

public:
	ParticleSystem(Vector3 initPos, GenerationSystems g);

	void Update(double t);



};

