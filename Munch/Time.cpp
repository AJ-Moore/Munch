
#include "Time.h"

namespace Munch{

	// Static members 
	U32 Time::deltaTime = 0; 
	U32 Time::timeElapsed = 0; 
	float Time::timeScale = 1.0f;
	
	// Constructor/ destructor
	Time::Time(){
		this->previousTimeElapsed = 0;
		this->timeElapsed = 0;
	}
	Time::~Time(){}

	// Wraps after 49days * timeScale
	int Time::getTimeElapsed(){
		return Time::timeElapsed; 
	}

	int Time::getTicks(){
		return SDL_GetTicks(); //!< Value return wraps after 49 days 
	}

	// Add the delta time to the time elapsed taking into account timescale
	void Time::update(){
		U32 _ticksElapsed = SDL_GetTicks();
		Time::deltaTime = (_ticksElapsed - this->previousTimeElapsed) * this->timeScale;
		this->timeElapsed += Time::deltaTime;

		this->previousTimeElapsed = _ticksElapsed;
	}




}