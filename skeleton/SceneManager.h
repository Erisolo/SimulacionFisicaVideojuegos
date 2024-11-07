#pragma once
//#include "Particle.h"
#include "ParticleSystem.h"
#include "ForceGenerator.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void Uptade(double t);
	void Shoot(char c, Vector3 pos);

	void deleteForceGenerator(int i);
	void deleteParticle(int i);
	void deleteParticleSystem(int i);


private:
	std::vector<Particle*> particles;
	std::vector<ParticleSystem*> sistemaParticulas;
	std::vector<ForceGenerator*> forceGenerators;

};

