#include "ParticleSystem.h"
#include <random>
#include <ostream>
#include <istream>
#include "ForceGenerator.h"

void ParticleSystem::deleteParticles()
{
	for (int i = 0; i < maxNumofParts; i++)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
		}
	}
	actNumOfParts = 0;
}

void ParticleSystem::deleteDeadParticles()
{
	for (int i = 0; i < maxNumofParts; i++)
	{
		if (particles[i] != nullptr && !particles[i]->alive())
		{
			delete particles[i];
			particles[i] = nullptr;
			actNumOfParts--;
		}
	}
}

void ParticleSystem::addParticle()
{
	bool added = false; int i = 0;
	Particle* p = generateParticle();


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

void ParticleSystem::updateParticles(double t)
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
		{
			particles[i]->Integrate(t);
		}
	}
}

Particle* ParticleSystem::generateParticle()
{
	Vector3 vel = meanVel; Vector3 pos = fuente;

	vel.x += normal_dist(seed) * velFac.x;
	vel.y += normal_dist(seed) * velFac.y;
	vel.z += normal_dist(seed) * velFac.z;

	pos.x += normal_dist(seed) * posFac.x;
	pos.y += normal_dist(seed) * posFac.y;
	pos.z += normal_dist(seed) * posFac.z;


	return new Particle(pos, vel, lifeTime, Vector4(0.96, 0.55, 0.91, 1), 1);
}

void ParticleSystem::asignateSystem(GenerationSystems g)
{
	switch (g)
	{
	case RAIN:
		meanVel = {0, -70, 0};
		velFac = { 0, 5, 0 };
		posFac = { 15, 0, 15 };
		lifeTime = 10;
		maxNumofParts = 500;
		framerate = 0.01;
		constantGen = true;
		break;
	case EXPLOSION:
		meanVel = { 0, 0, 0};
		velFac = { 60, 60, 60};
		posFac = { 0, 0, 0};
		lifeTime = 400;
		maxNumofParts = 100;
		framerate = 0.1;
		constantGen = false;
		break;
	case MANGUERA:
		meanVel = { -30, 60, -100};
		velFac = {5, 5, 5 };
		posFac = { 2, 0, 2};
		lifeTime = 4;
		maxNumofParts = 1000;
		framerate = 0.001;
		constantGen = true;
		break;
	case FIREWORKS:
		break;
	default:
		break;
	}

}

ParticleSystem::ParticleSystem(Vector3 initPos, GenerationSystems g, Vector3 systvel, double syslf): systemVel(systvel), sysLifetime(syslf)
{
	fuente = initPos;
	seed = std::mt19937();
	normal_dist = std::normal_distribution<>(0, 1); //generar un número aleatorio entre -1 y 1;
	asignateSystem(g);
	particles = std::vector<Particle*>(maxNumofParts);
	
	initSystem(g);

}

ParticleSystem::~ParticleSystem()
{
	deleteParticles();
}

void ParticleSystem::initSystem(GenerationSystems g)
{
	if (g == EXPLOSION)
	{
		for (int i = 0; i < maxNumofParts; i++)
		{
			addParticle();
		}
	}
}

void ParticleSystem::Update(double t)
{
	actTime += t;
	if (constantGen && maxNumofParts > actNumOfParts && actTime > framerate)
	{
		addParticle();
		actTime = 0;
	}
	if (sysLifetime > 0)
	{
		sysLifetime -= t;
		alive = sysLifetime > 0;

	}
	fuente += systemVel * t;
	updateParticles(t);
	deleteDeadParticles();
}

void ParticleSystem::aplyForceGenerators(std::vector<ForceGenerator*> &fg)
{
	for (int i = 0; i < fg.size(); i++)
	{
		if(fg[i] != nullptr)
			fg[i]->Update(particles, 0); //para no cambiar el tiempo
	}

}
