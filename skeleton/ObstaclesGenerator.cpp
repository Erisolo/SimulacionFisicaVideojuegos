#include "ObstaclesGenerator.h"

ObstaclesGenerator::ObstaclesGenerator(PxScene* s, PxPhysics* g, Vector3 pos, Vector3 vel, Vector3 acc, Vector3 size, float lf) : SolidsSystem(pos, s, g, NONE)
{
	framerate = 5;//sizeOfPath.z / vel.z;
	this->vel = vel;
	lifeTime = lf;
	actTime = 0;
	sizeOfPath = size;
}

ObstaclesGenerator::~ObstaclesGenerator()
{
}

void ObstaclesGenerator::generateNextObstacle()
{

	int b = 2;

	switch (b)
	{
	case 1: //piscina


		break;

	case 2: //saltar un solo bloque
		//makeFloor();
		solids.push_back(new RigidSolid("cube", scene, gP, fuente, vel, color, Vector3(sizeOfPath.x, 2, 5), 4, lifeTime, false, true)); //ccreando el bloque
		actNumOfSolids++;
		//creando el suelo

		break;

	case 3:
		break;

	case 4:
		break;

	case 5:
		break;

	default:
		break;
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
	deleteDeadSolids();

}

void ObstaclesGenerator::makeFloor()
{
	solids.push_back(new RigidSolid("cube", scene, gP, fuente, vel, color, sizeOfPath - Vector3(1), 5, 4, lifeTime));
	actNumOfSolids++;
}
