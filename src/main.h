#pragma once

#include "stdafx.h"
#include "FPSMeter.h"
#include "SkyBox.h"

bool NormalKeyboardKeys[256];
bool SpecialKeyboardKeys[256];

int g_WindowWidth = 1000;
int g_WindowHeight = 800;

float animationDT = 0.00005;
float animationDTIncrement = 0.0005;

void SpecialKeysCallback(int key,int x, int y);
void SpecialKeyUpCallback(int key, int x, int y);
void KeyboardCallback(unsigned char key,int x, int y);
void KeyboardKeyUpCallback(unsigned char key, int x, int y);
void ProcessInputKeys();
void ReshapeCallback(int w, int h);
void IdleCallback();
void DisplayCallback();