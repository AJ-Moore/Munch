#include "Material.h"

#include <sstream>
#include <fstream>

namespace Munch{

	Material::Material(){
	}

	Material::~Material(){
	}

	void Material::init(std::string Mat){
		this->materialFile = Mat; 
		this->matConfig.loadConfig(this->materialFile);
		this->textureFile = this->matConfig.getString("texture");
		this->fragShaderFile = this->matConfig.getString("frag_shader");
		this->vertShaderFile = this->matConfig.getString("vert_shader");

		U32 _texX = this->matConfig.getInt("tex_x");
		U32 _texY = this->matConfig.getInt("tex_y");

		// Load the texture 
		this->texture.init(this->textureFile, _texX, _texY);

		// Load shader 
		this->loadShader(); 
	}

	void Material::unload(){

		this->texture.unload(); 
	}

	void Material::bind(){
		glUseProgram(this->program);
		this->texture.bind(); 
	}

	/* Private function definitions */
	

	void Material::loadShader(){

		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string _fragShader, _vertShader;

		// Open frag shader and read to string
		std::fstream fStream;
		fStream.open(this->fragShaderFile.c_str(), std::fstream::in);

		// The current line being parsed 
		std::string _currentLine;

		while (std::getline(fStream, _currentLine)){
			_fragShader += _currentLine;
			_fragShader += "\n";
		}
		fStream.close();

		fStream.open(this->vertShaderFile.c_str(), std::fstream::in);

		while (std::getline(fStream, _currentLine)){
			_vertShader += _currentLine;
			_vertShader += "\n";
		}

		fStream.close();

		const char* _vertSource = _vertShader.c_str();
		const char* _fragSource = _fragShader.c_str();

		glShaderSource(vShader, 1, &_vertSource, NULL);
		glCompileShader(vShader);
		glShaderSource(fShader, 1, &_fragSource, NULL);
		glCompileShader(fShader);

		// Check if shaders compiled successfully 
		GLint success = 0;
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE){
			GLint logSize = 0;
			glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[4000];
			GLsizei length;
			glGetShaderInfoLog(vShader, 4000, &length, log);
			std::cout << "Vertex Shader Failed: " << log << std::endl;
		}
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE){
			GLint logSize = 0;
			glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logSize);
			char* log = new char[4000];
			GLsizei length;
			glGetShaderInfoLog(fShader, 4000, &length, log);
			std::cout << "Frag Shader Failed" << log << std::endl;
		}

		program = glCreateProgram();
		glAttachShader(program, vShader);
		glAttachShader(program, fShader);
		glLinkProgram(program);

		glUseProgram(program);

		glBindAttribLocation(program, 0, "Vertex");
		glBindAttribLocation(program, 1, "texCoordAtrib");

		GLint _texture = glGetUniformLocation(program, "tex");

		// set to texture unit 0
		glUniform1i(_texture, 0);

	}

	
	void Material::uniformMat4fv(std::string Name, U32 Size, bool Transpose,glm::mat4 Matrix){
		glUseProgram(this->program);
		GLuint _location = glGetUniformLocation(this->program, Name.c_str());
		glUniformMatrix4fv(_location, Size, Transpose, glm::value_ptr(Matrix));
	}


}