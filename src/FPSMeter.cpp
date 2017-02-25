#include "FPSMeter.h"

FPSMeter::FPSMeter() :
    m_FPS(0.0),
    m_IsCounting(false)
{
    #ifdef _WIN32
        #ifdef _WIN64
            m_Frequency = new LARGE_INTEGER();
            m_StartTime = new LARGE_INTEGER();
            m_EndTime = new LARGE_INTEGER();
            QueryPerformanceFrequency(m_Frequency);
        #endif
    #endif
}

FPSMeter::~FPSMeter()
{
    #ifdef _WIN32
        #ifdef _WIN64
            delete m_StartTime;
            delete m_EndTime;
            delete m_Frequency;
            delete m_pFPS;

            m_StartTime = nullptr;
            m_EndTime = nullptr;
            m_Frequency = nullptr;
            m_pFPS = nullptr;
        #endif
    #endif
}

FPSMeter* FPSMeter::GetCurrentInstance()
{
    if(m_pFPS == nullptr)
        m_pFPS = new FPSMeter();

    return m_pFPS;
}

double FPSMeter::GetFPS()
{
    return m_FPS;
}

string FPSMeter::GetFPSString()
{
    stringstream ss;
    ss << "FPS: " << m_FPS;
    return ss.str();
}

void FPSMeter::StartCounting()
{
    if(!m_IsCounting)
    {
        #ifdef _WIN32
            #ifdef _WIN64
                QueryPerformanceCounter(m_StartTime);
            #endif
        #elif __linux__
            m_StartTime = high_resolution_clock::now();
        #endif

        m_IsCounting = true;
    }
}

void FPSMeter::StopCounting()
{
    if(m_IsCounting)
    {
        #ifdef _WIN32
            #ifdef _WIN64
                QueryPerformanceCounter(m_EndTime);
                m_FPS = 1.0/((double)(m_EndTime->QuadPart - m_StartTime->QuadPart) / m_Frequency->QuadPart);
            #endif
        #elif __linux__
            m_EndTime = high_resolution_clock::now();
            duration<double,milli> timeDiff = m_EndTime-m_StartTime;
            m_FPS = 1000 / timeDiff.count();
        #endif

        m_IsCounting = false;
    }
}

FPSMeter* FPSMeter::m_pFPS = nullptr;
FPSMeter* fps = FPSMeter::GetCurrentInstance();