#include "Point.h"

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point Point::operator+(Vector3D v)
{
    return Point(this->x + v.x, this->y + v.y, this->z + v.z);
}