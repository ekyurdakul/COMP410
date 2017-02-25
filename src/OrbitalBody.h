#pragma once

#include "stdafx.h"
#include "Point.h"
#include "Textures.h"

class OrbitalBody
{
private:
	Point* position;
	GLuint textureID;
	float inclination;
	float animationAngle;
	float orbitalperiod;
	float selfRotAngle;
	float rotationperiod;
public:
	bool foundTeapot;
	Point* teapotLoc;
	float size;
	Point* currentPos;
	OrbitalBody(float dFromSun, float size, GLuint textureID, float inclination, float orbitalperiod, float rotationperiod);
	void Draw();
	void Animate(double dt);
};

extern OrbitalBody* sun;
extern OrbitalBody* mercury;
extern OrbitalBody* venus;
extern OrbitalBody* earth;
extern OrbitalBody* mars;
extern OrbitalBody* jupiter;
extern OrbitalBody* saturn;
extern OrbitalBody* uranus;
extern OrbitalBody* neptun;