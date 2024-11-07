#include "ForceGenerator.h"
#include "SceneManager.h"
void ForceGenerator::stop()
{
	mngr->deleteForceGenerator(id);
}
