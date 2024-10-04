#include "Proyectil.h"

void Proyectil::Integrate(double t)
{
	Pose.p = Pose.p + vel * t;
	vel = vel - gravedad * t; //aqui para acelerar (también la gravedad)
	//vel = vel * pow(damping, t);
}
