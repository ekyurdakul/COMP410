#pragma once

#include "stdafx.h"
#include "Camera.h"

class SkyBox
{
public:
	bool draw;
	SkyBox();
	void Draw();
};

extern SkyBox* sky;