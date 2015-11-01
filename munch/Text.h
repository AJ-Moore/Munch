#ifndef _MUNCH_TEXT
#define _MUNCH_TEXT

#include "common.h"
#include "Material.h"
#include "Component.h"
#include <vector>

namespace Munch{
	/** For renering text within the game.*/
	class Text : public Component{
	public:
		Text(Material* Material);
		~Text();

		virtual void init();
		virtual void update(); 
		virtual void render(); 
		virtual void unload();

	private:
		Text(){}

		/// Updates the buffer
		void updateBuffer(); 

		Material* material;

		/// The string to be displayed 
		std::string text; 

		/// The maximum available characters, determined by material.
		U8 maxCharacters;

		/// Ascii table offset, first character in character map 
		U8 asciiOffset; 

		/// Holds the vertex data 
		std::vector<float> vertices; 

		/// Holds the texture coords 
		std::vector<float> textureCoords; 

		/// The bitmap text buffer
		GLuint buffer;

		/// The current size of the buffer 
		U32 bufferSize; 

		/// The texture buffer size 
		U32 textureBufferSize;

		/// Determines whether buffer should be updated, when marked as true buffer is updated 
		bool isDirty;
	};

}

#endif 

