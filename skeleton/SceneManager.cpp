#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{
	delete part;
}

void SceneManager::init()
{
	//A METER COSAS VENGAAA

	part = new Particle(Vector3(0,0,0), Vector3(0,10,0), Vector3(0, 10, 0), 0.98); //por ahora solo eso
}

void SceneManager::Uptade(double t)
{
	part->Integrate(t);
}
