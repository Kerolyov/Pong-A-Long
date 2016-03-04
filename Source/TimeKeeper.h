#ifndef _SDLGL_TIMEKEEPER_H
#define _SDLGL_TIMEKEEPER_H

#include <sdl.h>

enum TimerState { STOPPED, PAUSED, GOING};

class TimeKeeper
{
public:
	TimeKeeper(void);
	~TimeKeeper(void);

	static bool initialize();

	static void update(bool frame_done = false);

	static double getDeltaTime();

	static double getCurrentTime();

	void startInterruption();
	void endInterruption();

	double getTimer();
	void Stop();
	void Start();
	void StartNonFrame();

	void unpause();
	void pause();

	TimerState getState();

private:
	static Uint64 m_freq;
	static Uint64 m_init_time;

	static double m_previous_time;
	static double m_current_time;

	double m_start_time;
	TimerState m_state;
};

//-------------------------------------------------------------
// Get delta time (between current and previous frame)

inline double TimeKeeper::getDeltaTime()
{
	return m_current_time - m_previous_time;
}


#endif // _TIMEKEEPER_H
