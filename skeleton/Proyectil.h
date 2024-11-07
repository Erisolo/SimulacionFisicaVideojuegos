#pragma once
#include "Particle.h"

class Proyectil: public Particle
{
private:
	Vector3 gravedad;
	float masa;

public:
	Proyectil(Vector3 pos, Vector3 vel, double d, double m, Vector3 g = {0, -9.8, 0}) : Particle(pos, vel, 5), masa(m), gravedad(g)
	{
		Pose = PxTransform(pos);

		renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &Pose, { 0.8, 0, 0.8, 1 });
	}
	void Integrate(double t) override;

};

