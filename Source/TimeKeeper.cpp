#include "TimeKeeper.h"

#include <assert.h> 

Uint64 TimeKeeper::m_freq = 0;
Uint64 TimeKeeper::m_init_time = 0;

double TimeKeeper::m_previous_time = 0.0;
double TimeKeeper::m_current_time = 0.0;


TimeKeeper::TimeKeeper()
: m_start_time(0.0), m_state(STOPPED)
{
}

TimeKeeper::~TimeKeeper()
{
}

//-------------------------------------------------------------
// Get (current) time since initialize()

double TimeKeeper::getCurrentTime()
{
	assert( m_freq );

	static double dFreq = static_cast<double>( m_freq );

	Uint64 t = SDL_GetPerformanceCounter() - m_init_time;

	return static_cast<double>(t) / dFreq ;
}

//-------------------------------------------------------------

bool TimeKeeper::initialize()
{
	m_freq = SDL_GetPerformanceFrequency();
	
	m_init_time = SDL_GetPerformanceCounter();

	m_current_time = m_previous_time = getCurrentTime();

	return true;
}

//-------------------------------------------------------------
void TimeKeeper::update(bool frame_done)
{
	if (!frame_done)
		m_previous_time = m_current_time;

	m_current_time = getCurrentTime();
}

//-------------------------------------------------------------
double TimeKeeper::getTimer()
{
	switch (m_state) 
	{
	case GOING:
		return m_current_time - m_start_time;
	case PAUSED:
		return m_start_time;
	default:
		return 0.f;
	}
}

void TimeKeeper::Stop()
{
	m_start_time = 0.0;
	m_state = STOPPED;
}

void TimeKeeper::Start()
{
	m_start_time = m_current_time;
	m_state = GOING;
}


void TimeKeeper::StartNonFrame()
{
	m_start_time = getCurrentTime();
	m_state = GOING;
}


//-------------------------------------------------------------
// Pause timer

void TimeKeeper::pause()
{
	m_start_time = m_current_time - m_start_time;
	m_state = PAUSED;
}

//-------------------------------------------------------------
// Unpause timer
//
// Notes:	Reported time continues from the time value when
//			the timer was paused

void TimeKeeper::unpause()
{
	m_start_time = m_current_time - m_start_time;
	m_state = GOING;
}

//-------------------------------------------------------------
// Get the current state of the timer
//
// Returns:	One of the following states:
//				STOPPED
//				GOING
//				PAUSED

TimerState TimeKeeper::getState()
{
	return m_state;
}

void TimeKeeper::startInterruption()
{
	Start();
}

void TimeKeeper::endInterruption()
{
	if (m_state == GOING)
		m_previous_time += getTimer();
	Stop();
}
