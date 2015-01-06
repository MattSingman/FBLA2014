#include <SDL.h>

#ifndef TIMER_H
#define TIMER_H

class timer {
	public:
		//Initializes variables
		timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		unsigned getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

private:
	//The clock time when the timer started
	unsigned startTicks;

	//The ticks stored when the timer was paused
	unsigned pausedTicks;

	//The timer status
	bool paused;
	bool started;
};

#endif