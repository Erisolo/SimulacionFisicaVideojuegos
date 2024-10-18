#pragma once
//#include "Particle.h"
#include "ParticleSystem.h"
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
	ParticleSystem* sistemaParticulas;
	

};

