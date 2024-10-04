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
			particles[i]->Integrate(t);
	}
}

void SceneManager::Shoot()
{
	particles.push_back(new Proyectil(Vector3(-20, 0, 0), Vector3(50, 30, 0), 0.98, 20000));
}
