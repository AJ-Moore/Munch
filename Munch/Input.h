
#ifndef _MUNCH_INPUT
#define _MUNCH_INPUT

#include "Common.h"
#include <map>
#include <vector>

namespace Munch{

	/** Bind targets for joystick binds*/
	enum JoyTarget{
		AXIS, 
		HAT,
		BUTTON
	};

	/** Abstract base class for bind*/
	class BindBase{
	public:
		BindBase(){}
		virtual void call(const float val) = 0;
	};

	/** Class for creating binds*/
	template <class T>
	class Bind : public BindBase{
	public:
		typedef void(T::*memberFunction)(const float);
		Bind(memberFunction Function, T* Obj){
			this->function = Function; 
			this->object = Obj;
		}
		~Bind(){}

		void call(const float val){
			(object->*function)(val);
		}
	private:
		memberFunction function; 
		T* object; 
		Bind(){ }
	};


	/**Handles input in the game*/
	class Input{
	public:
		Input();
		~Input();

		/// Must be called before use 
		void init(); 

		/// polls for input 
		void poll();

		/// Binds a given character keyboard key to a member function.
		template <class T>
		void addBind(SDL_Scancode Scancode, void(T::*memberFunction)(const float), T* Obj){
			this->keyboardBinds.insert(std::make_pair(Scancode,
					new Bind<T>(memberFunction, Obj)));
		}
		/*void addBind(SDL_Scancode Scancode, BindBase* Bind){
			this->keyboardBinds.insert(std::make_pair(Scancode, Bind));
		}*/

		//<summary>
		// Bind a given Joystick target to a memberFunction.
		//</summary>
		//<param name = "BindTarget"> Joystick bind target. </param>
		//<param name = "BindID"> The ID of the axis, button or hat to be bound to </param>
		//<param name = "JoystickID"> Which joystick to bind the function to</param>
		//<param name = "memberFunction"> The function to be bound </param>
		//<param name = "Obj"> Target object bound function should be called on </param>
		//<param name = "HatID"> Target SDL hat </param>
		template <class T> 
		void addBind(JoyTarget BindTarget, U8 BindID, U8 JoystickID, void(T::*memberFunction)(const float), T* Obj, U8 HatID = 0){

			if (JoystickID >= this->maxJoys){
				// Error 
				std::cout << "Error JoystickID exceeds maximum available joysticks" << std::endl; 
			}

			// Switch JoyTaret
			switch (BindTarget){
			case JoyTarget::AXIS:
				this->axisBinds[JoystickID].insert(std::make_pair(BindID, new Bind<T>(memberFunction, Obj)));
				break;
			case JoyTarget::BUTTON:
				this->joyBinds[JoystickID].insert(std::make_pair(BindID, new Bind<T>(memberFunction, Obj)));
				break;
			case JoyTarget::HAT:
			{
				// Totally legit solution
				U16 _hat = BindID << 8;
				_hat |= HatID;
				this->hatBinds[JoystickID].insert(std::make_pair(_hat, new Bind<T>(memberFunction, Obj)));
			}
				break;
			default:
				std::cout << "Joy target not found" << std::endl;
				break;
			}
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

		typedef std::multimap <U16, BindBase*> HatBinds; 
		HatBinds* hatBinds;

		// Maximum number of joysticks to be initialised 
		U8 maxJoys;

	};

}

#endif 