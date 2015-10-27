#include "Input.h"

namespace Munch{
	Input::Input(){
	}


	Input::~Input(){
	}

	void Input::poll(){
		SDL_Event _event;
		while (SDL_PollEvent(&_event)){
			// Keyboard binds multimap iterator
			std::pair <KeyboardBinds::iterator, KeyboardBinds::iterator> ret;
			switch (_event.type){
			case SDL_KEYDOWN:
				ret = this->keyboardBinds.equal_range(_event.key.keysym.scancode);
				for (KeyboardBinds::iterator iter = ret.first; iter != ret.second; ++iter){
					// Call callback
					iter->second->call(1.0f);
				}
				break;
			case SDL_KEYUP:
				ret = this->keyboardBinds.equal_range(_event.key.keysym.scancode);
				for (KeyboardBinds::iterator iter = ret.first; iter != ret.second; ++iter){
					// Call callback
					iter->second->call(0.0f);
				}
				break;

			default:
				break;
			}

		}
	}


}