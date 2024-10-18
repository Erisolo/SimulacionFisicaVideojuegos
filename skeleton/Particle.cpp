#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 pos, Vector3 Vel, Vector3 acc_, double d): vel(Vel), acc(acc_), damping(d)
{
	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &Pose, { 0.8, 0, 0.8, 1 });
	
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double lf, Vector4 col): vel(vel), acc(acc), lifeTime(lf)
{

	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &Pose, col);
	isAlive = true;

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
	/*vel = vel * pow(damping, dt);*/

	if (isAlive)
	{
		lifeTime -= dt;
		isAlive = lifeTime > 0;

	}
		
	/*acc = acc * damping;*/
	
}

void Particle::ChangeAcceleration(Vector3 acc_)
{
	acc = acc_;
}
