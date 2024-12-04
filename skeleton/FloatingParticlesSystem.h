#pragma once
#include "ParticleSystem.h"
class BuoyancyForceGenerator;

class FloatingParticlesSystem: public ParticleSystem
{
private:
	Particle* water;
	BuoyancyForceGenerator* waterForceGenerator;

public:
	FloatingParticlesSystem(Vector3 waterline, float density, float volume); 

	void attatchParticle(Particle* p);
	void deatatchParticle() { particles[0] = nullptr; }
	//SOLO PUEDE TENER UN LIQUIDO SUMERGIDO
	Particle* getAtatchedParticle() { return particles[0]; }

	void Update(double t) override;

	void aplyForceGenerators(std::vector<ForceGenerator*>& fg) override;
};

