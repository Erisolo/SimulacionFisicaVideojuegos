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

	part = new Particle({ 0,0,0 }, { 1,0,0 }); //por ahora solo eso
}

void SceneManager::Uptade(double t)
{
	part->Integrate(t);
}
