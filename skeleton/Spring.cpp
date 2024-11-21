#include "Spring.h"
#include "SpringForceGenerator.h"
void Spring::attatchParticle(Particle* p)
{
	if (actNumOfParts == particles.size())
	{
		int i = 0; bool added = false; //si hay algún spot libre
		while (!added && i < particles.size())
		{
			if (particles[i] == nullptr)
			{
				particles[i] = p;
				actNumOfParts++;
				added = true;
			}
			i++;
		}
	}
	else
	{
		particles.push_back(p);
		actNumOfParts++;
	}
	
}

void Spring::deatatchParticle(Particle* p)
{
	int i = 0; bool deleted = false; //si hay algún spot libre
	while (!deleted && i < particles.size())
	{
		if (particles[i] == p)
		{
			particles[i] = nullptr;
			actNumOfParts--;
			deleted= true;
		}
		i++;
	}
	
}

void Spring::changeStartingPoint(Particle* p)
{
	springForceGenerator->changeStartPoint(p);
}

void Spring::Update(double t)
{
	updateParticles(t); //integramos
	deleteDeadParticles();

}

void Spring::aplyForceGenerators(std::vector<ForceGenerator*>& fg)
{
	springForceGenerator->Update(particles);
	ParticleSystem::aplyForceGenerators(fg);
}

void Spring::changeK(float k)
{


}
