#include "Proyectil.h"

void Proyectil::Integrate(double t)
{
	Pose.p = Pose.p + vel * t;
	vel = vel - gravedad * t; //aqui para acelerar (tambi�n la gravedad)
	//vel = vel * pow(damping, t);
}
