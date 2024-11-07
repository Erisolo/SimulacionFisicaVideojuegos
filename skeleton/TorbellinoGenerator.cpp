#include "TorbellinoGenerator.h"

TorbellinoGenerator::TorbellinoGenerator( float Wi, Vector3 cntr, float roi, float hi): WindGenerator(Vector3(0), Wi, cntr, roi), huracaneIntensity(hi)
{
}

void TorbellinoGenerator::aplyForce(Particle* p, double dt)
{
	Vector3 posp = p->getPos();
	windSpeed = Vector3(-posp.z - center.z, 50 - (posp.y - center.y), posp.x - center.x) * huracaneIntensity;

	WindGenerator::aplyForce(p, dt);

}
