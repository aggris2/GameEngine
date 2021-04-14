#pragma once
#define WINDOWS_TIMER 0

#if WINDOWS TIMER
#include <Windows.h>
#else
#include <chrono>
#endif
namespace Allods2 {
#if WINDOWS TIMER


	class Timer {
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;
	public:
		Timer() {
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_Frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void reset() {
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed() {
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}
	};
#else
class Timer
{
private:
	typedef std::chrono::high_resolution_clock hrClock;
	typedef std::chrono::duration<float, std::milli> milliseconds_type;
	std::chrono::time_point<hrClock> m_Start;
public:
	Timer()
	{
		Reset();
	}

	void Reset()
	{
		m_Start = hrClock::now();
	}

	float elapsed()
	{
		return std::chrono::duration_cast<milliseconds_type>(hrClock::now() - m_Start).count() / 1000.0f;
	}
};
#endif

}