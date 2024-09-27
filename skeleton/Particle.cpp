#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 Vel)
{
	vel = Vel; //asignando la velocidad
	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(5)), &Pose, { 0.8, 0, 0.8, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::Integrate(double dt)
{
	Pose.p = Pose.p + vel * dt;
	//vel = velocity + (force / mass) * dt; //aqui para acelerar
	
}
