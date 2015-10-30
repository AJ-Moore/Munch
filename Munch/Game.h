

#ifndef _MUNCH_GAME
#define _MUNCH_GAME

#include "Common.h"
#include "Display.h"
#include "Time.h"
#include "Input.h"

namespace Munch{
	/*Central point for the application */
	class Game{
	public:
		Game();
		~Game();

		/// Main entry point for the game - starts the game loop 
		void mainLoop(); 

		/// Performs game initialisation - game will exit on return false
		bool init();

		/// Update game logic 
		void update(); 

		/// Render game 
		void render(); 

		/// Called to quit the game. 
		void quitGame(); 

		/// Display object used by the game, static for simplicity 
		static Display display;

		static Input input; 

	private: 

		/// Called to unload game (private)
		void unload();

		// Time keeping 
		Time time; 

		/// Whether the game is running (private)
		bool gameRunning; 

	};
}

#endif
