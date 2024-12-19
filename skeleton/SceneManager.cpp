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
	suelo = gPhysics->createRigidStatic(PxTransform(Vector3(0, 0, -200)));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 350), gPhysics->createMaterial(0.0f, 1.0f, 0.0f));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	RenderItem* renderitem = new RenderItem(shape, suelo, { 0.2, 0.7, 0.1, 1 });

	//now the side pannels of the floor
	PxRigidStatic* side1 = gPhysics->createRigidStatic(PxTransform(Vector3(60, 5, -200)));
	shape = CreateShape(PxBoxGeometry(40, 5, 270));
	side1->attachShape(*shape);
	scene->addActor(*side1);
	renderitem = new RenderItem(shape, side1, { 0.38, 0.96, 0.46, 1 });

	side1 = gPhysics->createRigidStatic(PxTransform(Vector3(-60, 5, -200)));
	shape = CreateShape(PxBoxGeometry(40, 5, 270));
	side1->attachShape(*shape);
	scene->addActor(*side1);
	renderitem = new RenderItem(shape, side1, { 0.38, 0.96, 0.46, 1 });


	//the force generators
	forceGenerators.push_back(new GravityGenerator(9.8));


	
	//rigids
	player = new RigidSolid("cube", scene, gPhysics, Vector3(0, 20, 0), Vector3(0), Vector4(8.9, 0, 3.2, 1), Vector3(2, 2, 2), 0.2, 0, true);
	solids.push_back(player);

	//making the obstacles
	obstacleGenerator = new ObstaclesGenerator(scene, gPhysics, Vector3(0, 3, -140), Vector3(0, 0, 50), Vector3(0.0), Vector3(20, 4, 30), 5);
	solidSystems.push_back(obstacleGenerator);



	//para combrobar colisiones
	player->getActor()->userData = (void*)"Player";
	suelo->userData = (void*)"Suelo";
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

	//comprobar si ha ganado el jugador
	if (obstacleGenerator != nullptr && !obstacleGenerator->isAlive())
	{
		gameWon();
	}
}

void SceneManager::Shoot(char c, Vector3 pos)
{
	switch (c)
	{
	case ' ':	//plosion
	{
		if (player != nullptr && player->getPos().y <=3 && player->getVel().magnitude() <= 1) //solo si está en el suelo quieto
		{
			//player->applyForce(Vector3(0, 35000, 0));
			player->setSpeed(Vector3(0, 20, 0));
		}
		break;
	}


	default:
		break;
	}
	
}

void SceneManager::onColision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	//el player solo puede colisionar de manera segura con el suelo. el resto es muerte
	if (!gameOver)
	{
		if ((static_cast<const char*>(actor1->userData) == "Player" && static_cast<const char*>(actor2->userData) != "Suelo") ||
			(static_cast<const char*>(actor2->userData) == "Player" && static_cast<const char*>(actor1->userData) != "Suelo"))
		{

			//forceGenerators.push_back(new ExplosionGenerator(player->getPos(), 1600000, 50, 1));
			sistemaParticulas.push_back(new ParticleSystem(player->getPos(), EXPLOSION));
			gameOver = true;
			lostGame();
		}

	}
	
}

void SceneManager::lostGame()
{
	delete obstacleGenerator; //borramos el generador de obstáculos
	obstacleGenerator = nullptr;
	solidSystems[0] = nullptr;
	//delete player;
	//player = nullptr;
}

void SceneManager::gameWon()
{
	delete obstacleGenerator; //borramos el generador de obstáculos
	solidSystems[0] = nullptr;

	//y hacemos la celebración
	sistemaParticulas.push_back(new ParticleSystem(Vector3(-50, 10, -15), MANGUERA));
	sistemaParticulas.push_back(new ParticleSystem(Vector3(50, 10, -15), MANGUERA));
	forceGenerators.push_back(new TorbellinoGenerator(0.7, Vector3(0, 10, 0), 500, 12));

}
