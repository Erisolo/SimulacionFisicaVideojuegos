#include "SceneManager.h"
#include "Proyectil.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
			delete particles[i];
	}
}

void SceneManager::init()
{
	//A METER COSAS VENGAAA

	
}

void SceneManager::Uptade(double t)
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
		{
			particles[i]->Integrate(t);
			if (particles[i]->hasTouchedGround())
			{
				delete particles[i];
				particles[i] = nullptr;
			}

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
