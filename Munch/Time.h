/*
Author: Allan J Moore 
Date: 21/10/2014
*/

#ifndef _MUNCH_TIME
#define _MUNCH_TIME

#include "Common.h"

namespace Munch{

	/** Time class - for time keeping*/
	class Time{
	public: 
		Time();
		~Time();

		/// The time passed (in milliseconds) since the last update. 
		static U32 deltaTime;

		/// Multiplier that effects the delta time. 
		static float timeScale;

		/// Get the current time elapsed in milliseconds (Affected by timeScale)
		/// Wraps after 49days * timeScale
		static int getTimeElapsed();

		/// Returns the time in milliseconds since the program was started
		static int getTicks();

		/// Called by the game once per frame
		void update();

	private:
		/// Previous number of ticks since program started(private)
		U32 previousTimeElapsed; 

		/// The time elapsed - affected by timescale
		static U32 timeElapsed;
	};


}

#endif 