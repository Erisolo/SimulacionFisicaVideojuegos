#include "Spring.h"
#include "SpringForceGenerator.h"
//crea un muelle entre las dos posiciones, con una particula a cada extremo(de masa 5) y k = 20.
Spring::Spring(Vector3 pos1, Vector3 pos2, float k)
{
	Particle* p = new Particle(pos1, Vector3(0), 5);

	particles.push_back(new Particle(pos2, Vector3(0), 5));
	
	float len = (pos1 - pos2).normalize();

	springForceGenerator = new SpringForceGenerator(p, k, len);


}
//crea un muelle entre las dos particulas, de distancia la q haya entre ellas.
Spring::Spring(Particle* p1, Particle* p2, float K)
{

	float len = (p1->getPos() - p2->getPos()).normalize();
	particles.push_back(p2);

	springForceGenerator = new SpringForceGenerator(p1, K, len);

}
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
	updateParticles(t);
	deleteDeadParticles();

}

void Spring::aplyForceGenerators(std::vector<ForceGenerator*>& fg)
{
	springForceGenerator->Update(particles);
	ParticleSystem::aplyForceGenerators(fg);
}

void Spring::changeK(float k)
{
	springForceGenerator->changeK(k);
}
