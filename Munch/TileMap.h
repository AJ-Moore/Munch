
#ifndef _MUNCH_TILEMAP
#define _MUNCH_TILEMAP

#include "Common.h"
#include "Material.h"
#include "Component.h"
#include <vector>
#include <string>

namespace Munch{
	/* Basic tile map implementation for game 'grid' */
	class TileMap : public Component{
	public:
		/// <summary>
		/// Creates a tile map of the requested size with the array passed in. 
		/// </summary> 
		/// <param name="Usize"> Unsigned Int 32 vec2 size of tilemap (width, height)
		/// <param name="Udata"> Vector unsigned int grid data. 
		/// <param name ="Mat"> Material used by the tile map. 
		TileMap(glm::vec2 Usize, std::vector<S32> Udata, Material* Mat);
		~TileMap();

		virtual void init(); 
		virtual void update();
		virtual void render(); 

		virtual void unload(); 

	private:
		TileMap(){}

		// Called to update the buffer data 
		void updateBuffer(); 

		/// Holds the tilemaps buffer ID
		GLuint bufferID; 

		/// Material used by tile map 
		Material* material; 

		/// Tile map data where value == id in texture atlas -1 not assigned
		std::vector<S32> data; 

		/// Dimensions of the tilemap 
		glm::vec2 uSize; 

		/// Holds the vertex data 
		std::vector<float> vertices; 

		/// Holds the texture coord data 
		std::vector<float> textureCoords; 

		/// The current size of the vertex buffer 
		U32 bufferSize; 

		/// The size of the texture buffer
		U32 textureBufferSize;

		/// Flag determines if buffer data should be updated
		bool isDirty; 

	};
}


#endif 
