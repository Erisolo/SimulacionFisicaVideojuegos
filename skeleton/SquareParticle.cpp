#include "SquareParticle.h"

SquareParticle::SquareParticle(Vector3 pos, Vector3 vel, float m, float w, float h, float d): height(h), width(w), depth(d), Particle(pos, vel, m)
{
	if (renderItem != nullptr)
	{
		DeregisterRenderItem(renderItem);
	}
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(width, height, depth)), &Pose, { 1, 1, 1, 1 });
}

SquareParticle::SquareParticle(Vector3 pos, Vector3 vel, double lf, Vector4 col, float m, float w, float h, float d): height(h), width(w), depth(d), Particle(pos, vel, lf, col, m)
{
	if (renderItem != nullptr)
	{
		DeregisterRenderItem(renderItem);
	}
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(width, height, depth)), &Pose, {1, 1, 1, 1});

}

void SquareParticle::init()
{
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(width, height, depth)), &Pose, {1, 1, 1, 1});
}
