#include "SceneManager.h"
#include "Proyectil.h"
#include "GravityGenerator.h"
#include "TorbellinoGenerator.h"
#include "ExplosionGenerator.h"
#include "Spring.h"
#include "FloatingParticlesSystem.h"
#include "SquareParticle.h"
#include "ObstaclesGenerator.h"

SceneManager::SceneManager()
{
	
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
			delete particles[i];
	}
	for (int i = 0; i < forceGenerators.size(); i++)
	{
		if (forceGenerators[i] != nullptr)
			delete forceGenerators[i];
	}
	for (int i = 0; i < sistemaParticulas.size(); i++)
	{
		if (sistemaParticulas[i] != nullptr)
			delete sistemaParticulas[i];
	}

	//delete sistemaParticulas;
}

void SceneManager::init()
{
	
	//setting up the floor
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform(Vector3(0, 0, -200)));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 350), gPhysics->createMaterial(0.0f, 1.0f, 0.0f));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	RenderItem* renderitem = new RenderItem(shape, suelo, { 0.2, 0.7, 0.1, 1 });

	//now the side pannels of the floor
	PxRigidStatic* side1 = gPhysics->createRigidStatic(PxTransform(Vector3(60, 5, -200)));
	shape = CreateShape(PxBoxGeometry(40, 5, 250));
	side1->attachShape(*shape);
	scene->addActor(*side1);
	renderitem = new RenderItem(shape, side1, { 0.38, 0.96, 0.46, 1 });

	side1 = gPhysics->createRigidStatic(PxTransform(Vector3(-60, 5, -200)));
	shape = CreateShape(PxBoxGeometry(40, 5, 250));
	side1->attachShape(*shape);
	scene->addActor(*side1);
	renderitem = new RenderItem(shape, side1, { 0.38, 0.96, 0.46, 1 });


	//the force generators
	forceGenerators.push_back(new GravityGenerator(9.8));


	
	//rigids
	player = new RigidSolid("cube", scene, gPhysics, Vector3(0, 20, 0), Vector3(0), Vector4(8.9, 0, 3.2, 1), Vector3(2, 2, 2), 0.2, 0, true);
	solids.push_back(player);

	//making the obstacles
	solidSystems.push_back(new ObstaclesGenerator(scene, gPhysics, Vector3(0, 3, -140), Vector3(0, 0, 50), Vector3(0.0), Vector3(20, 4, 30), 20));
}

void SceneManager::Uptade(double t)
{

	//en todos los updates fijamos al player en la posición
	for (int i = 0; i < sistemaParticulas.size(); i++)
	{
		if (sistemaParticulas[i] != nullptr)
		{
			sistemaParticulas[i]->Update(t);
			sistemaParticulas[i]->aplyForceGenerators(forceGenerators);
			//eliminar si se muere

		}
			
	}
	
	for (int i = 0; i < forceGenerators.size(); i++)
	{
		if (forceGenerators[i] != nullptr)
		{
			forceGenerators[i]->Update(particles, t);
			forceGenerators[i]->Update(solids);
			if (!forceGenerators[i]->isAlive())
			{
				delete forceGenerators[i];
				forceGenerators[i] = nullptr;
			}

		}

	}


	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
		{
			particles[i]->Integrate(t);
			//eliminar si se muere

		}
		
	}
	for (int i = 0; i < solidSystems.size(); i++)
	{
		if (solidSystems[i] != nullptr)
		{
			solidSystems[i]->Update(t);
			solidSystems[i]->aplyForceGenerators(forceGenerators);

		}

	}
}

void SceneManager::Shoot(char c, Vector3 pos)
{
	switch (c)
	{
	case 'P':	//plosion
	{
		//forceGenerators.push_back(new ExplosionGenerator(Vector3(0, 0, 0), 1600000, 50, 1));
		break;
	}
	case ' ':	//plosion
	{
		if (player->getPos().y <=3) //solo si está en el suelo
		{
			player->applyForce(Vector3(0, 30000, 0));
		}
		break;
	}


	default:
		break;
	}
	
}