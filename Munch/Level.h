
#ifndef _MUNCH_LEVEL 
#define _MUNCH_LEVEL

#include "Common.h"
#include <vector>

namespace Munch{
	/** Facilitates the functionality to load levels*/
	/// Level data is stored in byte format 
	/// Level Width = 40, Height = 24 
	/// Levels should be referenced by name alone
	class Level{
	public:
		Level();
		~Level();

		static const U8 LEVEL_WIDTH;
		static const U8 LEVEL_HEIGHT; 

		/// Loads a level with the given name. 
		void loadLevel(std::string levelName);

		/// Creates a new blank level and saves it to file 
		void newLevel(std::string levelName);

		/// Saves the currently loaded level with the name provided.
		void saveLevel(std::string levelName);

		/*Level Attributes*/
		
		/// The game tilemap data.
		std::vector<S32> data; //<! 40*24



	};

}
#endif 

