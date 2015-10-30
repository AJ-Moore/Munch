#include "MainGame.h"
#include "Input.h"
#include "Game.h"

namespace Munch{

	MainGame::MainGame(){
	}

	MainGame::~MainGame(){
	}

	void MainGame::wKey(float Val){
		std::cout << "W press: " << Val << std::endl;
	}

	void MainGame::init(){

		// Load the material 
		Material* _mat = new Material();
		_mat->init("assets/grid.material");

		std::vector<S32> _data;
		_data.resize(40 * 24);

		this->tileMap = new TileMap(glm::vec2(40,24),_data,_mat);
		this->tileMap->init();
		level.newLevel("Level1");

		// Test Input class 
		Game::input.addBind<MainGame>(SDL_SCANCODE_W, &MainGame::wKey, this);
		Game::input.addBind<MainGame>(JoyTarget::AXIS, 0, 0, &MainGame::wKey, this);
		
	}


	void MainGame::update(){
		this->tileMap->update();
	}

	void MainGame::render(){
		this->tileMap->render(); 
	}

	void MainGame::unload(){
		this->tileMap->unload(); 
		delete this->tileMap; 
	}


}