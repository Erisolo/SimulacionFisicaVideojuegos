#include "FloatingParticlesSystem.h"
#include "BuoyancyForceGenerator.h"
#include "SquareParticle.h"
FloatingParticlesSystem::FloatingParticlesSystem(Vector3 waterline, float density, float volume)
{
	water = new SquareParticle(waterline, Vector3(0.0), 5, 20, 1, 3);
	waterForceGenerator = new BuoyancyForceGenerator(water, 1, density, volume);
}
void FloatingParticlesSystem::attatchParticle(Particle* p)
{
	if (particles.size() == 0)
	{
		particles.push_back(p);
	}
	else
	{
		particles[0] = p;
	}
}
void FloatingParticlesSystem::Update(double t)
{
	updateParticles(t);
	deleteDeadParticles();
}

void FloatingParticlesSystem::aplyForceGenerators(std::vector<ForceGenerator*>& fg)
{
	waterForceGenerator->Update(particles);
	
	ParticleSystem::aplyForceGenerators(fg);

}
