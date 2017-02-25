#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include <math.h>
#include "lodepng.h"

using namespace std;

#ifdef _WIN32
	#ifdef _WIN64
		#include <Windows.h>
	#endif
#elif __linux__
	#include <chrono>
	using namespace chrono;
#endif