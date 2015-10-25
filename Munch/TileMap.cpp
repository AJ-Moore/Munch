#include "TileMap.h"
#include "Game.h"

namespace Munch{

	TileMap::TileMap(glm::vec2 USize, std::vector<S32> Data, Material* Mat){
		this->bufferSize = 0; 
		this->textureBufferSize = 0; 
		this->data = Data;
		this->material = Mat;
		this->uSize = USize;
	}


	TileMap::~TileMap(){

	}

	void TileMap::init(){

		glGenBuffers(1, &this->bufferID);
		
		// Resize the vector, 3 floats per vertex, 6 vertices per tile 
		this->vertices.resize((3*6)*(uSize.x*uSize.y));
		
		// Resize texture coord data 2 floats for each vertex 
		this->textureCoords.resize((2 * (3*6))*(uSize.x*uSize.y));

		this->updateBuffer(); 

	}

	void TileMap::update(){

		// If dirty update buffer data 
		if (this->isDirty){
			this->updateBuffer();
		}
	}

	void TileMap::render(){

		//Bind texture/ shader program
		this->material->bind();

		this->material->uniformMat4fv("wvpMat", 1, false, 
				Game::display.projMat * Game::display.viewMat * this->transform);

		glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);


		glDrawArrays(GL_TRIANGLES, 0, this->bufferSize / 3);

	}


	void TileMap::updateBuffer(){
		
		this->bufferSize = 0;
		this->textureBufferSize = 0;

		glm::vec2 tLeft(-(float)this->uSize.x / 2.0f, (float)this->uSize.y / 2);

		Texture *_texture = &this->material->texture;

		// Iterate through the tilemap data, work out vertex data & texture coords.
		std::vector<S32>::iterator iter;
		U32 _c = 0; 
		for ( iter = this->data.begin(); iter != this->data.end(); ++iter){
			if (*iter >= 0){

				U32 _tileX = _c % (U32)this->uSize.x;
				U32 _tileY = _c / this->uSize.x;

				// Every three represents a vertex 
				textureCoords[textureBufferSize + 0] = _texture->textureCoords._Myfirst[*iter][0].x;
				textureCoords[textureBufferSize + 1] = _texture->textureCoords._Myfirst[*iter][0].y;
				textureCoords[textureBufferSize + 2] = _texture->textureCoords._Myfirst[*iter][1].x;
				textureCoords[textureBufferSize + 3] = _texture->textureCoords._Myfirst[*iter][1].y;
				textureCoords[textureBufferSize + 4] = _texture->textureCoords._Myfirst[*iter][2].x;
				textureCoords[textureBufferSize + 5] = _texture->textureCoords._Myfirst[*iter][2].y;
				textureCoords[textureBufferSize + 6] = _texture->textureCoords._Myfirst[*iter][3].x;
				textureCoords[textureBufferSize + 7] = _texture->textureCoords._Myfirst[*iter][3].y;
				textureCoords[textureBufferSize + 8] = _texture->textureCoords._Myfirst[*iter][0].x;
				textureCoords[textureBufferSize + 9] = _texture->textureCoords._Myfirst[*iter][0].y;
				textureCoords[textureBufferSize + 10] = _texture->textureCoords._Myfirst[*iter][2].x;
				textureCoords[textureBufferSize + 11] = _texture->textureCoords._Myfirst[*iter][2].y;

				//bottom left 
				vertices[this->bufferSize + 0] = tLeft.x + _tileX;
				vertices[this->bufferSize + 1] = tLeft.y - _tileY - 1;

				//Top left
				vertices[this->bufferSize + 3] = tLeft.x + _tileX;
				vertices[this->bufferSize + 4] = tLeft.y - _tileY;

				//Top right
				vertices[this->bufferSize + 6] = tLeft.x + _tileX + 1;
				vertices[this->bufferSize + 7] = tLeft.y - _tileY;

				//bottom right 
				vertices[this->bufferSize + 9] = tLeft.x + _tileX + 1;
				vertices[this->bufferSize + 10] = tLeft.y - _tileY - 1;

				//bottom left
				vertices[this->bufferSize + 12] = tLeft.x + _tileX;
				vertices[this->bufferSize + 13] = tLeft.y - _tileY - 1;

				//Top right
				vertices[this->bufferSize + 15] = tLeft.x + _tileX + 1;
				vertices[this->bufferSize + 16] = tLeft.y - _tileY;



				this->bufferSize += 18;
				this->textureBufferSize += 12;
				_c++;
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(this->bufferSize + this->textureBufferSize), 
													0, GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*this->bufferSize, &this->vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*this->bufferSize, 
									sizeof(float)*this->textureBufferSize, &this->textureCoords[0]);

		// Vertices 
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

		// Texture coords 
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (GLvoid*)(sizeof(float) * this->bufferSize));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void TileMap::unload(){

	}

}