#pragma once
#include "Particle.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void Uptade(double t);
	void Shoot();


private:
	std::vector<Particle*> particles;
	

};

