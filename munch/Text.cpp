#include "Text.h"
#include "Game.h"

namespace Munch{


	Text::Text(Material* Mat){
		this->material = Mat;
		this->maxCharacters = 0;
		this->isDirty = true;
		this->asciiOffset = 48; 
		this->bufferSize = 0;
		this->text = "DEFAULT";
	}

	Text::~Text(){
	}

	void Text::init(){

		// Gen buffers 
		glGenBuffers(1, &this->buffer);

		// Retrieve the maximum available chracters in this map 
		glm::vec2 _size = this->material->getMapSize();

		this->maxCharacters = _size.x * _size.y;

	}

	void Text::update(){
		if (this->isDirty){
			this->updateBuffer();
			this->isDirty = false;
		}
	}

	void Text::render(){
		

		//Bind texture/ shader program
		this->material->bind();

		this->material->uniformMat4fv("wvpMat", 1, false,
			Game::display.projMat * Game::display.viewMat * this->transform);

		glBindBuffer(GL_ARRAY_BUFFER, this->buffer); 

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(float) * this->bufferSize));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLES, 0, this->bufferSize/ 3); 
	}

	void Text::unload(){

	}


	void Text::updateBuffer(){

		this->bufferSize = 0; 
		this->textureBufferSize = 0; 

		// Resize the container to account for the length of the text string.
		this->vertices.resize((6 * 3) * this->text.length());
		this->textureCoords.resize((6*2) * this->text.length());

		//Set elemtns to zero
		//std::fill(this->vertices.begin(), this->vertices.end(), 0);

		std::string::iterator iter;

		// Count.
		U32 _c = 0; 

		float _texWidth = 1.0f/ this->material->getMapSize().x;
		float _texHeight = 1.0f / this->material->getMapSize().y; 

		for (iter = this->text.begin(); iter != this->text.end(); ++iter){

			// Work out the texture to use for this chracter 
			S32 _char = ((*iter) - this->asciiOffset);

			if (_char >= 0 && _char < this->maxCharacters){

				//Texturs coords 
				this->textureCoords[this->textureBufferSize + 0] = this->material->texture.textureCoords._Myfirst[_char][0].x;
				this->textureCoords[this->textureBufferSize + 1] = this->material->texture.textureCoords._Myfirst[_char][0].y;

				this->textureCoords[this->textureBufferSize + 2] = this->material->texture.textureCoords._Myfirst[_char][1].x;
				this->textureCoords[this->textureBufferSize + 3] = this->material->texture.textureCoords._Myfirst[_char][1].y;

				this->textureCoords[this->textureBufferSize + 4] = this->material->texture.textureCoords._Myfirst[_char][2].x;
				this->textureCoords[this->textureBufferSize + 5] = this->material->texture.textureCoords._Myfirst[_char][2].y;

				this->textureCoords[this->textureBufferSize + 6] = this->material->texture.textureCoords._Myfirst[_char][3].x;
				this->textureCoords[this->textureBufferSize + 7] = this->material->texture.textureCoords._Myfirst[_char][3].y;

				this->textureCoords[this->textureBufferSize + 8] = this->material->texture.textureCoords._Myfirst[_char][0].x;
				this->textureCoords[this->textureBufferSize + 9] = this->material->texture.textureCoords._Myfirst[_char][0].y;

				this->textureCoords[this->textureBufferSize + 10] = this->material->texture.textureCoords._Myfirst[_char][2].x;
				this->textureCoords[this->textureBufferSize + 11] = this->material->texture.textureCoords._Myfirst[_char][2].y;

				this->vertices[this->bufferSize + 0] = _c;
				this->vertices[this->bufferSize + 1] = -1;

				this->vertices[this->bufferSize + 3] = _c;
				this->vertices[this->bufferSize + 4] = 0;

				this->vertices[this->bufferSize + 6] = _c + 1;
				this->vertices[this->bufferSize + 7] = 0;

				this->vertices[this->bufferSize + 9] = _c + 1;
				this->vertices[this->bufferSize + 10] = -1;

				this->vertices[this->bufferSize + 12] = _c;
				this->vertices[this->bufferSize + 13] = -1;

				this->vertices[this->bufferSize + 15] = _c + 1;
				this->vertices[this->bufferSize + 16] = 0;

			}
			_c++;
			this->bufferSize += 18;
			this->textureBufferSize += 12;
		}


		glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(this->bufferSize + this->textureBufferSize), 0, GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) *this->bufferSize, &this->vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)* this->bufferSize,
								sizeof(float)*this->textureBufferSize, &this->textureCoords[0]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(float) * this->bufferSize));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

	}


}