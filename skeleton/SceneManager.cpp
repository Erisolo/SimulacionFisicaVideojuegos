#include "SceneManager.h"
#include "Proyectil.h"
#include "GravityGenerator.h"
#include "TorbellinoGenerator.h"
#include "ExplosionGenerator.h"
#include "Spring.h"
#include "FloatingParticlesSystem.h"
#include "SquareParticle.h"
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
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform(Vector3(0.0)));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	RenderItem* renderitem = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });


	//now setting the particles and stuff
	//sistemaParticulas.push_back(new ParticleSystem(Vector3(0, 90, 0), RAIN));
	/*FloatingParticlesSystem* f = new FloatingParticlesSystem(Vector3(0, 40, 0), 1000);
	sistemaParticulas.push_back(f);
	Particle* floaty = new SquareParticle(Vector3(0, 41, 0), Vector3(0.0), 15, 1, 1, 1);
	f->attatchParticle(floaty, 2, 8);*/

	//the force generators
	// forceGenerators.push_back(new GravityGenerator(9.8));
	//forceGenerators.push_back(new TorbellinoGenerator(0.7, Vector3(0), 500, 12));
	//forceGenerators.push_back(new ExplosionGenerator(Vector3(0, 0, 0), 700, 500));
	//particles.push_back(new Particle(Vector3(0, 20, 0), Vector3(0), 1)); //particula de prueba
	
	//rigids
	solids.push_back(new RigidSolid("cube", scene, gPhysics, Vector3(0, 50, 0), Vector3(0), Vector4(8.9, 0, 3.2, 1), Vector3(5, 5, 5), 7));
	solids.push_back(new RigidSolid("badCube", scene, gPhysics, Vector3(20, 50, 0), Vector3(0), Vector4(8.9, 0, 3.2, 1), Vector3(5, 5, 5), 7));

	//solid sytems
	solidSystems.push_back(new SolidsSystem(Vector3(0, 50, 0), scene, gPhysics));
}

void SceneManager::Uptade(double t)
{
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
			//solidSystems[i]->aplyForceGenerators(forceGenerators);

		}

	}
}

void SceneManager::Shoot(char c, Vector3 pos)
{
	switch (c)
	{
	//case 'P': //proyectil normla
	//{
	//	particles.push_back(new Proyectil(pos, Vector3(-50, 10, -50), 0.98, 20000));
	//	break;
	//}
	//case 'G': //globo
	//{
	//	particles.push_back(new Proyectil(pos, Vector3(-20, 0, -20), 0.98, 2, Vector3(0, -2, 0)));
	//	break;
	//}
	//case 'B': //bala
	//{
	//	particles.push_back(new Proyectil(pos, Vector3(-120, 0, -120), 0.98, 2000));
	//	break;
	//}
	//case 'V': //vertical
	//{
	//	particles.push_back(new Proyectil(pos - Vector3(10), Vector3(-5, 20, -5), 0.98, 2000));
	//	break;
	//}
	case 'P':	//plosion
	{
		forceGenerators.push_back(new ExplosionGenerator(Vector3(0, 0, 0), 1600000, 50, 1));
		break;
	}


	default:
		break;
	}
	
}
