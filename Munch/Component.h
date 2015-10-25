
#ifndef _MUNCH_COMPONENT 
#define _MUNCH_COMPONENT

#include "Common.h"

namespace Munch{
	/** Base class for all components in the game - Abstract class can't be instantiated*/
	class Component{
	public:
		Component();
		~Component();

		/// Called to initialise the component
		virtual void init() = 0; //<! Pure virtual 

		/// Called to update the component 
		virtual void update();

		/// Called to render the component 
		virtual void render();

		/// Called to unload the component 
		virtual void unload();

		/// Sets the components rotation about the z axis 
		void setRotation(float Val);

		/// Sets the components position 
		void setPosition(glm::vec3 Position);

		/// Gets the components position
		glm::vec3 getPosition();

	protected:
		/// Vec3 position
		glm::vec3 position;

		/// Rotation about the z axis 
		float rotation;

		/// The components transformation matrix (Its position/ orientation in the world)
		glm::mat4 transform;

	private:
		/// Works out the transform matrix 
		void updateTransform();
	};

}

#endif 