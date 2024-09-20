#pragma once
#include <cmath>

class Vector3D
{
private:
	float x, y, z;

public:
	Vector3D(float nx, float ny, float nz): x(nx), y(ny), z(nz) {}

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	Vector3D normalize()
	{
		float mod = getModule();

		x = x / mod;
		y = y / mod;
		z = z / mod;

		return *this;
	}
	float getModule()
	{
		//puede hacerse también una variable módulo y simplemente recalcular el modulo si se hacen
		//cambios en el vector. pero creo q no voy a hacerlo
		return sqrt(x * x + y * y + z * z);
	}
	
	Vector3D operator=(const Vector3D& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
	Vector3D operator+(const Vector3D& other)
	{
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;

		return Vector3D(x, y, z);
	}
	Vector3D operator-(const Vector3D& other)
	{
		x = x - other.x;
		y = y - other.y;
		z = z - other.z;

		return Vector3D(x, y, z);
	}
	float operator*(const Vector3D& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	Vector3D operator*(const float& other)
	{
		x = x * other;
		y = y * other;
		z = z * other;

		return Vector3D(x, y, z);
	}


};

