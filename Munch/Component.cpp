#include "Component.h"

namespace Munch{

	Component::Component(){
		this->scale = glm::vec3(1, 1, 1);
	}


	Component::~Component(){
	}

	void Component::init(){
	}

	void Component::update(){

	}
 
	void Component::render(){

	}

	void Component::unload(){

	}

	// Simple/ effective enough for this purpose
	void Component::setRotation(float Val){
		this->rotation = Val;
		this->updateTransform();
	}

	void Component::setScale(glm::vec3 Scale){
		this->scale = Scale;
		this->updateTransform();
	}

	void Component::setPosition(glm::vec3 Position){
		this->position = Position; 
		this->updateTransform(); 
	}

	/// returns the position 
	glm::vec3 Component::getPosition(){
		return this->position; 
	}

	// Useful reference material on glm: http://glm.g-truc.net/0.9.5/code.html
	void Component::updateTransform(){
		// Set to identy 
		this->transform = glm::mat4(0);

		this->transform = glm::translate(glm::mat4(1.0f), this->position);
		this->transform = glm::rotate(this->transform, this->rotation, glm::vec3(0,0,1.0f));
		this->transform = glm::scale(this->transform, this->scale);
	}

}