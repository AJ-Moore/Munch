
#ifndef _MUNCH_INPUT
#define _MUNCH_INPUT

#include "Common.h"
#include <map>
#include <vector>

namespace Munch{

	/** Abstract base class for bind*/
	class BindBase{
	public:
		BindBase(){}
		virtual void call(const float val) = 0;
	};

	/** Class for creating binds*/
	template <class T>
	class Bind{
	public:
		typedef void(T::*memberFunction)(const float)
		Bind(memberFunction Function, T* Obj){
			this->function = Function; 
			this->object = Obj;
		}
		~Bind(){}

		void call(const float val){
			(Object->*function)(val);
		}
	private:
		memeberFunction function; 
		T* object; 
		Bind(){ }
	};

	/**Handles input in the game*/
	class Input{
	public:
		Input();
		~Input();

		/// polls for input 
		void poll();

		/// Binds a given character keyboard key to a member function.
		template <class T>
		void addBind(SDL_Scancode, void(T::*memberFunction)(const float), T* Obj){
			this->keyboardBinds.insert(std::make_pair(SDL_Scancode,
					new Bind<T>(memberFunction, Obj)));
		}


	private:
		/// Map holds keyboard binds 
		typedef std::multimap<SDL_Scancode, BindBase*> KeyboardBinds;
		KeyboardBinds keyboardBinds;

		/// Map for joy axis binds, U8 Axis 
		typedef std::multimap <U8, BindBase*> AxisBinds; 
		AxisBinds* axisBinds;//!< array of maxJoys 

		typedef std::multimap <U8, BindBase*> JoyBinds;
		JoyBinds* joyBinds;

		// Maximum number of joysticks to be initialised 
		U8 maxJoys;

	};

}

#endif 