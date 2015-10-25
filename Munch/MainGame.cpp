#include "MainGame.h"

namespace Munch{

	MainGame::MainGame(){
	}

	MainGame::~MainGame(){
	}

	void MainGame::init(){

		// Load the material 
		Material* _mat = new Material();
		_mat->init("assets/grid.material");

		std::vector<S32> _data;
		_data.resize(30 * 20);

		this->tileMap = new TileMap(glm::vec2(30,20),_data,_mat);
		this->tileMap->init();
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