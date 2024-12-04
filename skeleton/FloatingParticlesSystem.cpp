#include "FloatingParticlesSystem.h"
#include "BuoyancyForceGenerator.h"
#include "SquareParticle.h"
FloatingParticlesSystem::FloatingParticlesSystem(Vector3 waterline, float density)
{
	water = new SquareParticle(waterline, Vector3(0.0), 5, 20, 1, 5);
	waterForceGenerator = new BuoyancyForceGenerator(water, 0, density, 0);
}
void FloatingParticlesSystem::attatchParticle(Particle* p, float height, float volume)
{
	if (particles.size() == 0)
	{
		particles.push_back(p);
	}
	else
	{
		particles[0] = p;
	}

	waterForceGenerator->changeObjectProperties(height, volume);
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
