
#ifndef _MUNCH_MATERIAL
#define _MUNCH_MATERIAL 

#include "Common.h"
#include "Config.h"
#include "Texture.h"

namespace Munch{
	/* Facilitates all our basic texture and shader needs - nothing special */
	/* Pros: simple*/
	/* Cons: not very optimal*/
	class Material{
	public:
		///Constructor 
		Material();
		~Material();

		/// Init - loads shader and texture data. 
		void init(std::string Material);

		/// Unloads material performs cleanup 
		void unload();

		/// Binds the shader program and texture... 
		void bind(); 

		/// The texture used by this program.
		Texture texture;

		/* Maintaing simplicity provide*/

		/// Sets the uniform
		void uniformMat4fv(std::string Name, U32 Size, bool Transpose, glm::mat4 Matrix);

	private: 
		/// Loads the shader program.
		void loadShader(); 

		/// Frag shader file 
		std::string fragShaderFile; 

		/// Vert shader file 
		std::string vertShaderFile; 

		/// Texture file dir + filename 
		std::string textureFile; 

		/// Material file 
		std::string materialFile; 

		/// Shader program used by this material.
		GLuint program; 

		/// Material configuration file.
		Config matConfig; 

	};
}

#endif