#include "Texture.h"

namespace Munch{
	Texture::Texture(){
		this->textureID = -1;
		this->sliceX = 1;
		this->sliceY = 1;
	}


	Texture::~Texture(){
	}

	Texture::Texture(std::string File, U32 SplitX, U32 SplitY){
		this->textureFile = File; 

		if (SplitX == 0)
			this->sliceX = 1;
		else
			this->sliceX = SplitX;

		if (SplitY == 0)
			this->sliceY = 1;
		else
			this->sliceY = SplitY; 
	}

	Texture::Texture(std::string File){
		Texture(File, 1, 1);
	}

	void Texture::init(){
		this->loadTexture(); 
		this->genTextureCoords();
	}

	void Texture::init(std::string File, U32 SplitX, U32 SplitY){
		if (this->textureID != -1)
			glDeleteTextures(1, &this->textureID);

		this->textureID = -1; 

		this->textureFile = File;
		if (SplitX == 0)
			this->sliceX = 1;
		else
			this->sliceX = SplitX;

		if (SplitY == 0)
			this->sliceY = 1;
		else
			this->sliceY = SplitY;
		
		this->init();
	}

	void Texture::bind(){
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}
 
	void Texture::unload(){
		if (this->textureID != -1)
			glDeleteTextures(1, &this->textureID);

		textureID = -1;

		this->textureCoords.resize(this->sliceX*this->sliceY);
		std::vector<glm::vec2*>::iterator iter;
		for (iter = this->textureCoords.begin(); iter != this->textureCoords.end(); ++iter){
			delete[](*iter);
		}
	}

	void Texture::loadTexture(){
		SDL_Surface* image = IMG_Load(this->textureFile.c_str());

		if (image == NULL){
			std::cout << ("Unable to load texture?: Error: %s", SDL_GetError());
			// use default texture...
			return;
		}

		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);

		U32 _format = 0;
		if (image->format->Amask)
			_format = GL_RGBA;
		else
			_format = GL_RGB;


		//Texture info passed from sdl surface
		glTexImage2D(GL_TEXTURE_2D,
			0,//Mipmap Level
			_format, //bit per pixel
			image->w,
			image->h,
			0,//texture border 	
			_format,
			GL_UNSIGNED_BYTE,
			image->pixels);

		// Set texture parameters 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//glGenerateMipmap(GL_TEXTURE_2D);


		// Free image/ sdl surface 
		SDL_FreeSurface(image);
	}


	void Texture::genTextureCoords(){

		this->textureCoords.resize((this->sliceX*this->sliceY) * 4);

		std::vector<glm::vec2*>::iterator iter;
		for (iter = this->textureCoords.begin(); iter != this->textureCoords.end(); ++iter){
			*iter = new glm::vec2[4]();
		}

		// Work out the width + height of each texture in atlas
		float _width = 1.0f / this->sliceX; 
		float _height = 1.0f / this->sliceY;

		for (U32 _x = 0; _x < this->sliceX; _x++){
			for (U32 _y = 0; _y < this->sliceX; _y++){

				// Bottom left
				this->textureCoords[(_y * this->sliceX) + _x][0].x = _width * _x;
				this->textureCoords[(_y * this->sliceX) + _x][0].y = 1.0f - ((_y+1) * _height); 
				
				// Top left
				this->textureCoords[(_y * this->sliceX) + _x][1].x = _width * _x;
				this->textureCoords[(_y * this->sliceX) + _x][1].y = 1.0f - (_y * _height);

				// Top right
				this->textureCoords[(_y * this->sliceX) + _x][2].x = _width * (_x + 1);
				this->textureCoords[(_y * this->sliceX) + _x][2].y = 1.0f - (_y * _height);

				// Bottom right 
				this->textureCoords[(_y * this->sliceX) + _x][3].x = _width * (_x + 1);
				this->textureCoords[(_y * this->sliceX) + _x][3].y = 1.0f - ((_y + 1) * _height);

			}
		}


	}
}