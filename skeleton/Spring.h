#pragma once
class SpringForceGenerator;
#include "ParticleSystem.h"

class Spring: public ParticleSystem //no tiene nada q ver pero bueno aqui está
{
private:
	SpringForceGenerator* springForceGenerator;
	//cosas de particle system

public:
	Spring(Vector3 pos1, Vector3 pos2, float k = 70); //crea sus propias particulas a la distancia q quieres
	Spring(Particle* p1, Particle* p2, float K);

	void attatchParticle(Particle* p);
	void deatatchParticle(Particle* p);
	void changeStartingPoint(Particle* p);

	void Update(double t) override;

	void aplyForceGenerators(std::vector<ForceGenerator*>& fg) override;

	void changeK(float k);
};

