#include "MainGame.h"
#include "Input.h"

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
		Input input; 
		input.init();
		input.addBind<MainGame>(SDL_SCANCODE_W, &MainGame::wKey, this);

		
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