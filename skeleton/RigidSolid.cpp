#include "RigidSolid.h"

RigidSolid::RigidSolid(std::string sh, PxScene* s, PxPhysics* gP, Vector3 pos, Vector3 vel, Vector4 col, Vector3 size, float mass)
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

		ix = (1.0f / 12.0f) * mass * (size.y * size.y + size.z * size.z);
		iy = (1.0f / 12.0f) * mass * (size.x * size.x + size.z * size.z);
		iz = (1.0f / 12.0f) * mass * (size.x * size.x + size.y * size.y);
		body->setMassSpaceInertiaTensor({ ix, iy, iz });
	}
	//else if ...

	//adding everything together
	body->attachShape(*shape);
	if (sh == "cube")
	{
		PxRigidBodyExt::updateMassAndInertia(*body, mass);
	}
	s->addActor(*body);

	//and now so we can see it
	renderItem = new RenderItem(shape, body, col);

}
