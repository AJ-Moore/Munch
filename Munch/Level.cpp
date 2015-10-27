#include "Level.h"
#include <fstream>

namespace Munch{

	const U8 Level::LEVEL_WIDTH = 40; 
	const U8 Level::LEVEL_HEIGHT = 24; 

	Level::Level(){
		this->data.resize(this->LEVEL_HEIGHT*this->LEVEL_WIDTH);
	}


	Level::~Level(){
	}

	void Level::loadLevel(std::string levelName){

	}

	void Level::saveLevel(std::string levelName){

		// Open the file for writing 
		std::ofstream ofStream("assets/levels/" + levelName, std::ios::binary);

		// Write the tilemap data as byte data 
		std::vector<S32>::iterator iter; 

		for (iter = this->data.begin(); iter != this->data.end(); ++iter){
			// Write data to file 
			ofStream.write((char*)(&(*iter)), sizeof(S32));
		}

		// Close the file 
		ofStream.close();
	}

	void Level::newLevel(std::string levelName){
		///initialise vector to -1 
		this->data.resize(this->LEVEL_HEIGHT*this->LEVEL_WIDTH);
		std::fill(this->data.begin(), this->data.end(), 1);

		this->saveLevel(levelName);
	}


}

