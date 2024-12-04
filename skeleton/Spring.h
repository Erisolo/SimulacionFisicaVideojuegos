#pragma once
class SpringForceGenerator;
#include "ParticleSystem.h"

//SOLO PUEDE TENER UNA PARTICULAS ATATCHADA AL MISMO TIEMPO
class Spring: public ParticleSystem //no tiene nada q ver pero bueno aqui está
{
private:
	SpringForceGenerator* springForceGenerator;
	bool staticSP;
	//cosas de particle system

public:
	Spring(Vector3 pos1, Vector3 pos2, float k = 70, bool sp = true, bool negf = true); //crea sus propias particulas a la distancia q quieres
	Spring(Particle* p1, Particle* p2, float K = 70, bool sp = true, bool negf = true);

	void attatchParticle(Particle* p);
	void deatatchParticle();
	void changeStartingPoint(Particle* p);

	void Update(double t) override;

	void aplyForceGenerators(std::vector<ForceGenerator*>& fg) override;

	void changeK(float k);
};

