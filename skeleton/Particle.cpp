#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 pos, Vector3 Vel, float m, float lf): vel(Vel), myMass(m), lifeTime(lf)
{
	forces = Vector3(0);
	Pose = PxTransform(pos);

	this->init();
	
}

Particle::Particle(Vector3 pos, Vector3 vel, double lf, Vector4 col, float m): vel(vel), lifeTime(lf)
{
	myMass = m;
	forces = Vector3(0);
	Pose = PxTransform(pos);

	
	isAlive = true;


	//this->init();
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(0.5)), &Pose, col);
}

void Particle::init()
{
	renderItem = new RenderItem( CreateShape(PxSphereGeometry(0.5)), &Pose, { 1, 1, 1, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::Integrate(double dt)
{
	if (forces != Vector3(0))
	{
		acc = forces / myMass;
		vel = vel + acc * dt; //aqui para acelerar

	}
		
	Pose.p = Pose.p + vel * dt;

	if (lifeTime > 0)	//se comprueba solo si tiene lifetime
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

void Particle::applyForce(Vector3 fc)
{
	forces += fc; 
}
