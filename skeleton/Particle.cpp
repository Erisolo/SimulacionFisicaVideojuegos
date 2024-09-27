#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 Vel)
{
	vel = Vel; //asignando la velocidad
	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(5)), &Pose, { 1, 1, 1, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::Integrate(double t)
{
}
