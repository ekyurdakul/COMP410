#pragma once

#include "stdafx.h"
#include "Vector3D.h"

class Point
{
public:
	float x,y,z;
	Point(float x, float y, float z);
	Point operator+(Vector3D v);
};