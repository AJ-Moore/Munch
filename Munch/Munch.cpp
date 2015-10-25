/*
Author: Allan J Moore
Date: 21/10/2014
*/

// Main entry point for application. 

#include "Common.h"
#include "Game.h"

int main(int argc, char** argv){

	Munch::Game _game; 
	_game.mainLoop();

	std::cin.get();

	return 0; 
}