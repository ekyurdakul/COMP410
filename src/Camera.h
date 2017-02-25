#pragma once

#include "stdafx.h"
#include "OrbitalBody.h"

class Camera
{
private:
	double speed;
	double angle;
	double lightspeedmult;
	bool followPlanet;
	OrbitalBody* following;
	vector<OrbitalBody*> planets;
public:
	Point position;
	Vector3D forward, normal, side;
	int teapotsFound;

	Camera();
	void PitchDown();
	void PitchUp();
	void RollLeft();
	void RollRight();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void MoveUp();
	void MoveDown();
	void JumpToLightspeed();
	void YawLeft();
	void YawRight();
	void CheckForTeapotDiscovery();
	void Teleport(int planetIndex);
	void SetupProjection();
};

extern Camera* c;