#include "Vector3D.h"

Vector3D::Vector3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D Vector3D::operator*(double s)
{
    return Vector3D(this->x * s, this->y*s, this->z*s);
}

Vector3D Vector3D::operator+(Vector3D v)
{
    return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3D normalizeVector(Vector3D v)
{
	float n = sqrt(v.x*v.x + v.y*v.y+ v.z*v.z);
	return Vector3D(v.x/n,v.y/n,v.z/n);
}

Vector3D crossProduct(Vector3D a, Vector3D b)
{
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	return normalizeVector(Vector3D(x,y,z));
}

float vectorSize(Vector3D v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}