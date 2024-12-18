#include "RigidSolid.h"

RigidSolid::RigidSolid(std::string sh, PxScene* s, PxPhysics* gP, Vector3 pos, Vector3 vel, Vector4 col, Vector3 size, float mass, float t, bool lockin, bool lockedOtherWay)
{
	//we create the rigid
	trans = PxTransform(pos);
	body = gP->createRigidDynamic(trans);
	body->setLinearVelocity(vel);

	//we create the shape
	PxShape* shape;
	
	PxMaterial* material = gP->createMaterial(0.0f, 1.0f, 1.0f); //para q no bote nadie
	if (sh == "cube")
	{
		shape = CreateShape(PxBoxGeometry(size), gP->createMaterial(0.0f, 1.0f, 0.0f));
	}
	else if (sh == "ball")
	{
		shape = CreateShape(PxSphereGeometry(size.x), gP->createMaterial(0.0f, 1.0f, 0.0f));
	}

	//adding everything together
	
	body->attachShape(*shape);

	if (lockin)
	{
		//body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);

		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
		//body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
	}
	else if (lockedOtherWay)
	{
		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
		body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);
	}
	
	//body->setSleepThreshold(5.0f);
	//body->createShape(PxBoxGeometry(size), *material);
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
	body->addForce(fc);
	
}

void RigidSolid::setSpeed(Vector3 s)
{
	body->setLinearVelocity(s);
}

Vector3 RigidSolid::getPos()
{
	return (body->getGlobalPose().p);
}

Vector3 RigidSolid::getVel()
{
	return body->getLinearVelocity();
}

void RigidSolid::setPosXZ(Vector3 pos)
{


}
