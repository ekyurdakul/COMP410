#pragma once

#include "stdafx.h"

#define textureCount 10
#define sphereSlice 128
#define sphereStack 128

extern GLuint textures[textureCount];
extern string textureFiles[textureCount];

void Draw2DText(float x, float y, string text);