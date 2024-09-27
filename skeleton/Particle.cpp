#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 Vel, Vector3 acc_)
{
	vel = Vel; //asignando la velocidad
	acc = acc_;
	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &Pose, { 0.8, 0, 0.8, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::Integrate(double dt)
{
	Pose.p = Pose.p + vel * dt;
	vel = vel+ acc * dt; //aqui para acelerar
	
}

void Particle::ChangeAcceleration(Vector3 acc_)
{
	acc = acc_;
}
