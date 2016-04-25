#pragma once
#include <Windows.h>
#include <stdio.h>

class CTimer
{
public:
	LARGE_INTEGER Freq, StartTime, EndTime, ThisTime, LastTime;
	double fFreq;
	double TotalTime;

	CTimer ( )
	{
		QueryPerformanceFrequency ( &Freq );
		fFreq = ( double ) Freq.QuadPart;
		TotalTime = 0;
	}

	~CTimer ( )
	{

	}

	void StartTimer ( )
	{
		QueryPerformanceCounter ( &StartTime );
		ThisTime = LastTime = StartTime;
		TotalTime = 0.0;
	}

	double StopTimer ( )
	{
		QueryPerformanceCounter ( &EndTime );
		TotalTime = ( EndTime.QuadPart - StartTime.QuadPart ) / fFreq;

		return TotalTime;
	}

	double GetTimeElapsedSinceStart ( )
	{
		LastTime = ThisTime;
		QueryPerformanceCounter ( &ThisTime );
		TotalTime += ( ThisTime.QuadPart - LastTime.QuadPart ) / fFreq;

		return TotalTime;
	}
};

