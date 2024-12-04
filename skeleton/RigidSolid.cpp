#include "RigidSolid.h"

RigidSolid::RigidSolid(std::string sh, PxScene* s, PxPhysics* gP, Vector3 pos, Vector3 vel, Vector4 col, Vector3 size, float mass, float t)
{
	//we create the rigid
	body = gP->createRigidDynamic(PxTransform(pos));
	body->setLinearVelocity(vel);

	//we create the shape
	PxShape* shape;
	float ix, iy, iz; //for inercia
	if (sh == "cube")
	{
		shape = CreateShape(PxBoxGeometry(size));

		

	}
	else if (sh == "badCube")
	{
		shape = CreateShape(PxBoxGeometry(size)); 
	}
	//else if ...

	//adding everything together
	body->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*body, mass);
	
	s->addActor(*body);

	//and now so we can see it
	renderItem = new RenderItem(shape, body, col);

	//finally, so it can be alive:
	lifeTime = t;
	isAlive = true;

}

RigidSolid::~RigidSolid()
{
	PxScene* scene = body->getScene();
	if (scene) {
		scene->removeActor(*body);
	}

	// Libera el objeto
	body->release();
	body = nullptr;

	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void RigidSolid::update(double dt)
{
	if (lifeTime > 0)	//se comprueba solo si tiene lifetime
	{
		lifeTime -= dt;
		isAlive = lifeTime > 0;

	}
}

void RigidSolid::applyForce(Vector3 fc)
{
}
