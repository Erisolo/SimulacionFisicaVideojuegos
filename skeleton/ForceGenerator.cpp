#include "ForceGenerator.h"
#include "Particle.h"
void ForceGenerator::Update(std::vector<Particle*> &ps, double dt)
{
	if (alive)
	{
		for (int i = 0; i < ps.size(); i++)
		{
			if (ps[i] != nullptr)
				this->aplyForce(ps[i], dt);

		}
	}
}
