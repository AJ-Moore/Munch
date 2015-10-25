#include "GameState.h"

namespace Munch{

	// Static members
	GameState* GameState::currentState = nullptr;

	GameState::GameState(){
	}

	GameState::~GameState(){
	}

	void GameState::init(){
	
	}

	void GameState::update(){

	}

	void GameState::render(){

	}

	void GameState::unload(){

	}

	void GameState::changeState(GameState* state){
		if (GameState::currentState != nullptr){
			GameState::currentState->unload();
			delete GameState::currentState;
		}

		state->init(); 
		GameState::currentState = state; 	
	}

	// Update render and unload state 

	void GameState::updateState(){
		if (GameState::currentState != nullptr)
			GameState::currentState->update();
	}

	void  GameState::renderState(){
		if (GameState::currentState != nullptr)
			GameState::currentState->render();
	}

	void GameState::unloadState(){
		if (GameState::currentState != nullptr){
			GameState::currentState->unload();
			delete GameState::currentState;
		}
	}
}