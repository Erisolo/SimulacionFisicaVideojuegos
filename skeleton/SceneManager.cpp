#include "SceneManager.h"
#include "Proyectil.h"
#include "GravityGenerator.h"

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
	//delete sistemaParticulas;
}

void SceneManager::init()
{
	//sistemaParticulas = new ParticleSystem(Vector3(0, 0, 0), MANGUERA);
	forceGenerators.push_back(new GravityGenerator(9.8));
	particles.push_back(new Particle(Vector3(0, 50, 0), Vector3(0), Vector3(0), 5)); //particula de prueba
	
}

void SceneManager::Uptade(double t)
{
	//sistemaParticulas->Update(t);

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
		{
			particles[i]->Integrate(t);

			for (int j = 0; j < forceGenerators.size(); j++) //we pass it to the generators to apply forces to
			{
				if (forceGenerators[i] != nullptr)
					forceGenerators[i]->aplyForce(particles[i]);

			}
			/*if (particles[i]->hasTouchedGround())
			{
				delete particles[i];
				particles[i] = nullptr;
			}*/

		}
		
	}
}

void SceneManager::Shoot(char c, Vector3 pos)
{
	switch (c)
	{
	case 'P': //proyectil normla
	{
		particles.push_back(new Proyectil(pos, Vector3(-50, 10, -50), 0.98, 20000));
		break;
	}
	case 'G': //globo
	{
		particles.push_back(new Proyectil(pos, Vector3(-20, 0, -20), 0.98, 2, Vector3(0, -2, 0)));
		break;
	}
	case 'B': //bala
	{
		particles.push_back(new Proyectil(pos, Vector3(-120, 0, -120), 0.98, 2000));
		break;
	}
	case 'V': //vertical
	{
		particles.push_back(new Proyectil(pos - Vector3(10), Vector3(-5, 20, -5), 0.98, 2000));
		break;
	}


	default:
		break;
	}
	
}
