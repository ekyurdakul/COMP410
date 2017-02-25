#pragma once

#include "stdafx.h"

class Vector3D
{
public:
	float x,y,z;
	Vector3D(float x, float y, float z);
	Vector3D operator*(double s);
	Vector3D operator+(Vector3D v);
};

Vector3D normalizeVector(Vector3D v);
Vector3D crossProduct(Vector3D a, Vector3D b);
float vectorSize(Vector3D v);