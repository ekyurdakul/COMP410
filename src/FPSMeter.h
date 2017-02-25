#pragma once

#include "stdafx.h"

class FPSMeter
{
private:
	#ifdef _WIN32
		#ifdef _WIN64
			LARGE_INTEGER* m_Frequency;
			LARGE_INTEGER* m_StartTime;
			LARGE_INTEGER* m_EndTime;
		#endif
	#elif __linux__
		time_point<high_resolution_clock> m_StartTime;
		time_point<high_resolution_clock> m_EndTime;
	#endif
	static FPSMeter* m_pFPS;
	double m_FPS;
	bool m_IsCounting;
	FPSMeter();
public:
	~FPSMeter();
	static FPSMeter* GetCurrentInstance();
	double GetFPS();
	string GetFPSString();
	void StartCounting();
	void StopCounting();
};

extern FPSMeter* fps;