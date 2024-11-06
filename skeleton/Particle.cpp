#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 pos, Vector3 Vel, Vector3 acc_, float m): vel(Vel), acc(acc_), myMass(m)
{
	forces = Vector3(0);
	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &Pose, { 1, 1, 1, 1 });
	
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double lf, Vector4 col): vel(vel), acc(acc), lifeTime(lf)
{
	forces = Vector3(0);
	Pose = PxTransform(pos);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &Pose, { 1, 1, 1, 1 });
	isAlive = true;

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::Integrate(double dt)
{
	acc = forces/myMass;
	
	vel = vel + acc * dt; //aqui para acelerar
	Pose.p = Pose.p + vel * dt;
	
	/*vel = vel * pow(damping, dt);*/

	if (isAlive)
	{
		lifeTime -= dt;
		isAlive = lifeTime > 0;

	}

	//we reset the forces
	forces = Vector3(0);
		
	/*acc = acc * damping;*/ //fuck damping all my homies hate damping
	
}

void Particle::ChangeAcceleration(Vector3 acc_)
{
	acc = acc_;
}
