#include "Spring.h"
#include "SpringForceGenerator.h"
//crea un muelle entre las dos posiciones, con una particula a cada extremo(de masa 5) y k = 20.
Spring::Spring(Vector3 pos1, Vector3 pos2, float k, bool sp, bool negf)
{
	staticSP = sp;
	Particle* p = new Particle(pos1, Vector3(0), 5);

	particles.push_back(new Particle(pos2, Vector3(0), 5));
	
	float len = (pos1 - pos2).normalize();

	springForceGenerator = new SpringForceGenerator(p, k, len, sp, negf);

}
//crea un muelle entre las dos particulas, de distancia la q haya entre ellas.
Spring::Spring(Particle* p1, Particle* p2, float K, bool sp, bool negf)
{
	staticSP = sp;
	float len = (p1->getPos() - p2->getPos()).normalize();
	particles.push_back(p2);

	springForceGenerator = new SpringForceGenerator(p1, K, len, sp, negf);

}
void Spring::attatchParticle(Particle* p)
{
	particles[0] = p;
	
}

void Spring::deatatchParticle()
{
	particles[0] = nullptr;
	
}

void Spring::changeStartingPoint(Particle* p)
{
	springForceGenerator->changeStartPoint(p);
}

Spring::Spring(RigidSolid* p1, Particle* p2, float K, bool sp, bool negf)
{
	staticSP = sp;
	float len = (p2->getPos() - p1->getPos()).normalize();
	solids.push_back(p1);

	springForceGenerator = new SpringForceGenerator(p2, K, len, sp, negf);
}

void Spring::Update(double t)
{
	//siempre q el origen siga vivo, lo actualizamos todo
	updateParticles(t);

	//if (!staticSP)
	springForceGenerator->getStartPoint()->Integrate(t); //peor de los casos, velocidad 0

	deleteDeadParticles();
}

void Spring::aplyForceGenerators(std::vector<ForceGenerator*>& fg)
{
	if (particles.size() > 0)
	{
		springForceGenerator->Update(particles);

		if (!staticSP)
		{
			particles.push_back(springForceGenerator->getStartPoint());
			ParticleSystem::aplyForceGenerators(fg);
			particles.pop_back();
		}

		else
		{
			ParticleSystem::aplyForceGenerators(fg);
		}

	}
	else if (solids.size() > 0)
	{
		springForceGenerator->Update(solids);
		//ParticleSystem::aplyForceGenerators(fg);

	}
	
}

void Spring::changeK(float k)
{
	springForceGenerator->changeK(k);
}
