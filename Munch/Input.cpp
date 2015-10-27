#include "Input.h"

namespace Munch{
	Input::Input(){
		this->maxJoys = 4;
	}


	Input::~Input(){
	}

	void Input::init(){
		this->joyBinds = new JoyBinds[this->maxJoys](); 
		this->axisBinds = new AxisBinds[this->maxJoys](); 
		this->hatBinds = new HatBinds[this->maxJoys]();
	}

	void Input::poll(){
		SDL_Event _event;
		while (SDL_PollEvent(&_event)){
			
			// Holds range of enteries returned from multimap
			std::pair <KeyboardBinds::iterator, KeyboardBinds::iterator> keyRange;
			std::pair <AxisBinds::iterator, AxisBinds::iterator> axisRange;
			std::pair <JoyBinds::iterator, JoyBinds::iterator> joyRange;
			std::pair <HatBinds::iterator, HatBinds::iterator> hatRange;

			switch (_event.type){
			case SDL_KEYDOWN:
				keyRange = this->keyboardBinds.equal_range(_event.key.keysym.scancode);
				for (KeyboardBinds::iterator iter = keyRange.first; iter != keyRange.second; ++iter){
					// Call callback
					iter->second->call(1.0f);
				}
				break;
			case SDL_KEYUP:
				keyRange = this->keyboardBinds.equal_range(_event.key.keysym.scancode);
				for (KeyboardBinds::iterator iter = keyRange.first; iter != keyRange.second; ++iter){
					// Call callback
					iter->second->call(0.0f);
				}
				break;
			case SDL_JOYAXISMOTION:
				if (_event.jaxis.which >= this->maxJoys){
					break;
				}
				axisRange = this->axisBinds[_event.jaxis.which].equal_range(_event.jaxis.axis);
				for (AxisBinds::iterator iter = axisRange.first; iter != axisRange.second; ++iter){
					iter->second->call(_event.jaxis.value);
				}
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				if (_event.jaxis.which >= this->maxJoys)
					break;
				joyRange = this->axisBinds[_event.jbutton.which].equal_range(_event.jbutton.button);
				for (JoyBinds::iterator iter = joyRange.first; iter != joyRange.second; ++iter){
					if (_event.jbutton.state & SDL_PRESSED){
						iter->second->call(1.0f);
					}
					else{
						iter->second->call(0);
					}
				}
				break;
			case SDL_JOYHATMOTION:
				hatRange = this->hatBinds[_event.jhat.which].equal_range(((U16)(_event.jhat.which << 8)) | (U16)_event.jhat.value);
				for (HatBinds::iterator iter = hatRange.first; iter != hatRange.second; ++iter){
					iter->second->call(1.0f);
				}
				break;
			default:
				break;
			}

		}
	}


}