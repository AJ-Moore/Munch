

#ifndef _MUNCH_DISPLAY
#define _MUNCH_DISPLAY

#include "Common.h"

namespace Munch{
	class Display{
	public:
		Display();
		~Display();

		void setDisplay(int x, int y, int width, int height);

		/// Called to init the window.
		bool init(); 

		/// Swaps the SDL window 
		void swapOPGLWindow();

		/// Should be called before exiting
		void Display::unload();

		/// The view matrix 
		glm::mat4 viewMat;

		/// The project matrix 
		glm::mat4 projMat;

	private: 
		/*Various window settings */
		/// Window rect 
		int x, y, width, height; 

		/// The SDL window 
		SDL_Window* window; 

		/// The OpenGL Context 
		SDL_GLContext glContext; 


	};
}

#endif