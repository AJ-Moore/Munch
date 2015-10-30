#include "Game.h"

#include "GameState.h"
#include "MainGame.h"

namespace Munch{

	// Static members 
	Display Game::display;
	Input Game::input;

	Game::Game(){
		this->gameRunning = false; 
	}
	
	Game::~Game(){
	}

	bool Game::init(){
		
		display.setDisplay(100, 100, 1280, 720);
		if (!display.init()){
			return false;
		}

		Game::input.init();
		
		return true;
	}

	void Game::mainLoop(){
		
		if (this->init()){
			//Set initial state here... 
			GameState::changeState(new MainGame());
			this->gameRunning = true; 
			while (this->gameRunning){
				this->update(); 
				this->render(); 
			}
		}
		else{
			std::cout << "Game initialisation failed" << std::endl; 
		}

		// Unloads game 
		this->unload(); 
	}

	void Game::update(){
		SDL_PumpEvents(); 
		time.update();
		input.poll();

		// Update the current game state. 
		GameState::updateState();

	}

	void Game::render(){
		this->display.swapOPGLWindow(); 

		glClear(GL_COLOR_BUFFER_BIT);

		GameState::renderState(); 
	}

	void Game::unload(){

		// Unload state 
		GameState::unloadState();

		// Unloads display, destroys SDL window + OGL context 
		this->display.unload();
	}

	void Game::quitGame(){
		this->gameRunning = false; 
	}


}