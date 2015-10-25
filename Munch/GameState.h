
#ifndef _MUNCH_GAMESTATE
#define _MUNCH_GAMESTATE

#include "Common.h"

namespace Munch{
	/* Simplistic means to handle states in the game.*/
	class GameState{
		friend class Game; 
	public:
		GameState();
		~GameState();

		/// inits current state. 
		virtual void init(); 

		/// Updates the current state.
		virtual void update();

		/// Renders the current state. 
		virtual void render();

		/// Unloads the current state.
		virtual void unload();

		/// Changes the current state to the one specified.
		static void changeState(GameState* state);

	private:
		static GameState* currentState;

		/// Called to update the current state.
		static void updateState(); 

		/// Called to render the current state.
		static void renderState();

		/// Call on exit to unload state/ s .
		static void unloadState();

	};
}
#endif 
