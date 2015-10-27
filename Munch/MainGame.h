#pragma once

#ifndef _MUNCH_MAINGAME
#define _MUNCH_MAINGAME

#include "Common.h"
#include "GameState.h"
#include "TileMap.h"
#include "Level.h"

namespace Munch{
	/*The game itself.*/
	class MainGame : public GameState{
	public:
		MainGame();
		~MainGame();

		virtual void init(); 
		virtual void update();
		virtual void render(); 
		virtual void unload(); 

		void wKey(float Val);

	private:
		/// The tile map used for the 'maze' map
		TileMap *tileMap;

		/// Holds level data, facilitates the loading unloading of levels.
		Level level; 
	};

}

#endif 
