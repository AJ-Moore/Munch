
#ifndef _MUNCH_TEXTURE 
#define _MUNCH_TEXTURE

#include "Common.h"
#include <vector> 

namespace Munch{
	/** Handles the textures we will be using.*/
	class Texture{
	public:
		Texture();

		///<summary> 
		/// Texture constructor 
		///</summary> 
		///<param name="File"> The path and file name of the texture file 
		///<param name="SplitX"> For texture atlas how many horizontal divisions 1 | 0 = nodivision. 
		///<param name="SplitY"> For texture atlad number of verticle divisions. 1 | 0 = nodivision. 
		Texture(std::string File, U32 SplitX, U32 SplitY);

		///<param name="File"> The path and file name of the texture file 		
		Texture(std::string File);

		~Texture();

		/// Loads the texture and binds it. 
		void init();

		/// Init with the provided texture 
		void init(std::string File, U32 SplitX, U32 SplitY);

		/// Called to bind texture state.
		void bind(); 

		/// Unloads the texture data from memory, should be called on exit. 
		void unload(); 

		/// Contains a list of sorted texture coordinates 
		std::vector<glm::vec2*> textureCoords;

	private:

		/// Loads the texture
		void loadTexture();

		/// Generates texture coordonates 
		void genTextureCoords();

		/// Filepath of the texture 
		std::string textureFile;

		/// The texture ID 
		GLuint textureID; 

		/// How many subdivisions in this atlas?
		U32 sliceX, sliceY;

		/// Default texture data... 

	};
}

#endif