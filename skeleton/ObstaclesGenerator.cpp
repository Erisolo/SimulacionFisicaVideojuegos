#include "ObstaclesGenerator.h"
#include "Spring.h"

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
		//generamos lluvia
		particleSystems.push_back(new ParticleSystem(Vector3(fuente.x, 80, fuente.y), RAIN, vel));

	}
	else
	{
		int b = 5;
		switch (b)
		{
		case 2: //saltar un solo bloque
			solids.push_back(new RigidSolid("cube", scene, gP, fuente, vel, color, Vector3(sizeOfPath.x, 2, 5), 4, lifeTime, false, true)); //ccreando el bloque
			actNumOfSolids++;
			break;

		case 3:
			//dos bloques con techo
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(10, 2, 0), vel, color, Vector3(sizeOfPath.x / 2 - 3, 4, 5), 4, lifeTime, false, true)); //ccreando el bloque
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(-10, 2, 0), vel, color, Vector3(sizeOfPath.x / 2 - 3, 4, 5), 4, lifeTime, false, true)); //ccreando el bloque
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(0, 8, 0), vel, color, Vector3(sizeOfPath.x, 2, 5), 4, lifeTime, false, true)); //ccreando el bloque
			actNumOfSolids += 2;
			break;

		case 4:	//bola q va de un lado a otro a por ti
			particleSystems.push_back(new Spring(new RigidSolid("ball", scene, gP, fuente + Vector3(12, 0, 0), Vector3(-40, 0, 0), color, sizeOfPath/5, 2, lifeTime), 
				new Particle(fuente - sizeOfPath/2, vel, 4), 400)); //se crea un nuevo muelle y se le aplica una fuerza
			break;
		case 5:
			//bloque más alto
			solids.push_back(new RigidSolid("cube", scene, gP, fuente + Vector3(0,2,0), vel, color, Vector3(sizeOfPath.x, 4, 5), 4, lifeTime, false, true)); //ccreando el bloque
			actNumOfSolids++;

			break;

		default:
			break;
		}
		numobstPassed++;
	}
	

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

