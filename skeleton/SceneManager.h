#pragma once
//#include "Particle.h"
#include "ParticleSystem.h"
#include "ForceGenerator.h"
class Spring;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void Uptade(double t);
	void Shoot(char c, Vector3 pos);


private:
	std::vector<Particle*> particles;
	std::vector<ParticleSystem*> sistemaParticulas;
	std::vector<ForceGenerator*> forceGenerators;

	Spring* spring;
};

