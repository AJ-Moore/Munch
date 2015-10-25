#include "Display.h"

namespace Munch{
	Display::Display(){
		this->x = 0; 
		this->y = 0; 
		this->width = 800; 
		this->height = 600; 

		this->window = nullptr; 
	}

	Display::~Display(){
	}

	void Display::setDisplay(int X, int Y, int Width, int Height){
		this->x = X; 
		this->y = Y; 
		this->width = Width;
		this->height = Height; 
	}

	bool Display::init(){
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			std::cout << "Unable to init SDL" << std::endl;
			return false; 
		}

		// init SDL_image + png library 
		IMG_Init(IMG_INIT_PNG);

		this->window = SDL_CreateWindow("Munch", this->x, this->y, width, height, SDL_WINDOW_OPENGL);

		// Create the OpenGL context for the window 
		this->glContext = SDL_GL_CreateContext(this->window);

		// init glew 
		glewInit(); 

		// Set the OGL clear colour 
		glClearColor(0, 0, 0, 1); //!< By default we'll want this black
		//glClearColor(0.5f, 0.5f, 1.0f, 1.0f); //debug*

		// Set blend function
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Set our viewport to the window extent 
		glViewport(0, 0, this->width, this->height);

		// Set the viewport + view matrix, no point doing anything fancy/ dynamic for pacman
		glm::vec3 _position(0.0f, 0.0f, 20.0f);
		glm::vec3 _target(0.0f, 0.0f, 0.0f);
		glm::vec3 _up(0.0, 1.0f, 0.0f);

		// Initialise our view + projection matrices 
		viewMat = glm::lookAt(_position, _target, _up);
		projMat = glm::perspective(45.0f, (float)this->width / (float)this->height, 0.1f, 1000.0f);

		return true;

	}

	// Should be called before exiting
	void Display::unload(){
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(this->window);

		SDL_Quit(); 
	}

	void Display::swapOPGLWindow(){
		SDL_GL_SwapWindow(this->window);
	}

}