#include "ObstaclesGenerator.h"
#include "Spring.h"
#include <random>
#include <algorithm>
//#include <cmath>
//#include <iostream>
ObstaclesGenerator::ObstaclesGenerator(PxScene* s, PxPhysics* g, Vector3 pos, Vector3 vel, Vector3 acc, Vector3 size, float lf) : SolidsSystem(pos, s, g, NONE)
{
	framerate = 5;//sizeOfPath.z / vel.z;
	this->vel = vel;
	lifeTime = lf;
	actTime = 0;
	sizeOfPath = size;
}

void ObstaclesGenerator::aplyForceGenerators(std::vector<ForceGenerator*>& fg)
{
	for (int i = 0; i < particleSystems.size(); i++)
	{
		if (particleSystems[i] != nullptr)
		{
			particleSystems[i]->aplyForceGenerators(fg);
		}

	}
	SolidsSystem::aplyForceGenerators(fg);
}

ObstaclesGenerator::~ObstaclesGenerator()
{
}

void ObstaclesGenerator::generateNextObstacle()
{
	if (numobstPassed != 0 && numobstPassed % obsToRain == 0)
	{
		//comprobamos si ha ganado
		if (numobstPassed == obsToWin)
		{
			alive = false;
		}
		else
		{
			particleSystems.push_back(new ParticleSystem(Vector3(fuente.x, 80, fuente.z), RAIN, vel, lifeTime));
		}

	}
	else
	{
		//choosea random one
		std::random_device rd;
		std::mt19937 gen(rd());
		std::normal_distribution<> d(1.5, 0.5); // Media en 1.5, desviación estándar 0.5

		// Ajustar el valor generado al rango 0-3 
		int b = std::round(d(gen));
		if (b < 0) b = 0;
		if (b > 3) b = 3;


		switch (b)
		{
		case 2: //saltar un solo bloque
			solids.push_back(new RigidSolid("cube", scene, gP, fuente, vel, color, Vector3(sizeOfPath.x, 2, 5), 4, lifeTime, false, true)); //ccreando el bloque
			actNumOfSolids++;
			break;

		case 1:
			//dos bloques con techo
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(10, 2, 0), vel, color, Vector3(sizeOfPath.x / 2 - 3, 4, 5), 4, lifeTime, false, true)); //ccreando el bloque
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(-10, 2, 0), vel, color, Vector3(sizeOfPath.x / 2 - 3, 4, 5), 4, lifeTime, false, true)); //ccreando el bloque
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(0, 8, 0), vel, color, Vector3(sizeOfPath.x, 2, 5), 4, lifeTime, false, true)); //ccreando el bloque
			actNumOfSolids += 2;
			break;

		case 0:	//bola q va de un lado a otro a por ti
			particleSystems.push_back(new Spring(new RigidSolid("ball", scene, gP, fuente + Vector3(12, 0, 0), Vector3(-40, 0, 0), color, sizeOfPath/5, 2, lifeTime), 
				new Particle(fuente - sizeOfPath/2, vel, 4, lifeTime), 400)); //se crea un nuevo muelle y se le aplica una fuerza
			break;
		case 3:
			//bloque más alto
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(0,2,0), vel, color, Vector3(sizeOfPath.x, 4, 5), 4, lifeTime, false, true)); //ccreando el bloque
			actNumOfSolids++;

			break;

		default:
			break;
		}
		
	}
	numobstPassed++;

}

void ObstaclesGenerator::Update(double dt)
{
	actTime += dt;
	if (actTime > framerate)
	{
		generateNextObstacle();
		actTime = 0;
	}

	updateSolids(dt);
	updateParticleSystems(dt);
	deleteDeadSolids();
	deleteDeadSystems();

}

void ObstaclesGenerator::makeFloor()
{
	solids.push_back(new RigidSolid("cube", scene, gP, fuente, vel, color, sizeOfPath - Vector3(1), 5, 4, lifeTime));
	actNumOfSolids++;
}

void ObstaclesGenerator::updateParticleSystems(double dt)
{
	for (int i = 0; i < particleSystems.size(); i++)
	{
		if (particleSystems[i] != nullptr)
		{
			particleSystems[i]->Update(dt);
		}
	}

}

void ObstaclesGenerator::deleteDeadSystems()
{
	for (int i = 0; i < particleSystems.size(); i++)
	{
		if (particleSystems[i] != nullptr && !particleSystems[i]->isAlive())
		{
			delete particleSystems[i];
			particleSystems[i] = nullptr;
		}
	}
}

void ObstaclesGenerator::insert(RigidSolid* r)
{
	bool added = false; int i = 0;

	while (!added && i < solids.size())
	{
		if (solids[i] == nullptr)
		{
			solids[i] = r;
			added = true;
		}
		i++;
	}
	if (!added)
		solids.push_back(r);
}

void ObstaclesGenerator::inster(ParticleSystem* s)
{
	bool added = false; int i = 0;

	while (!added && i < solids.size())
	{
		if (particleSystems[i] == nullptr)
		{
			particleSystems[i] = s;
			added = true;
		}
		i++;
	}
	if (!added)
		particleSystems.push_back(s);
}

