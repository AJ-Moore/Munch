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

		Material* _font = new Material(); 
		_font->init("assets/font.material");

		std::vector<S32> _data;
		_data.resize(40 * 24);

		name = new Text(_font);
		name->init();
		name->setScale(glm::vec3(1.5f, 1.5f, 1.5f));

		this->tileMap = new TileMap(glm::vec2(40,24),_data,_mat);
		this->tileMap->init();
		//this->tileMap->setScale(glm::vec3(0.1f,0.1f,0.1f));
		level.newLevel("Level1");

		// Test Input class 
		Game::input.addBind<MainGame>(SDL_SCANCODE_W, &MainGame::wKey, this);
		Game::input.addBind<MainGame>(JoyTarget::AXIS, 0, 0, &MainGame::wKey, this);


		
	}


	void MainGame::update(){
		this->tileMap->update();
		name->update();
	}

	void MainGame::render(){
		//this->tileMap->render(); 
		name->render(); 
	}

	void MainGame::unload(){
		this->tileMap->unload(); 
		delete this->tileMap; 
	}


}