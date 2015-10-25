#include "Config.h"

#include <sstream>
#include <fstream>

Config::Config()
{
}


Config::~Config()
{
}

// very simple and quite flawed
void Config::loadConfig(std::string File){

	// Clear the current properties.
	this->properties.clear(); 

	// Open file 
	std::fstream fStream; 
	fStream.open(File.c_str(), std::fstream::in);

	// The current line being parsed 
	std::string _currentLine; 

	while (std::getline(fStream, _currentLine)){

		// Try and find the first occurance of an '=' else continue 
		U32 _pos = _currentLine.find_first_of('=');

		// If '=' could not be found 
		if (_pos == std::string::npos)
			continue;

		//else seperate the string + create a property. 
		std::string _key = _currentLine.substr(0, _pos);
		std::string _val = _currentLine.substr(_pos + 1, std::string::npos);

		Property<std::string, std::string> _prop(_key, _val);

		this->properties.push_back(_prop);

	}
}

std::string Config::getString(std::string PropertyName){
	std::vector<Property<std::string, std::string>>::iterator iter; 

	for (iter = this->properties.begin(); iter != this->properties.end(); ++iter){
		if (iter->key == PropertyName){
			return iter->value; 
		}
	}

	return "";

}

S32 Config::getInt(std::string PropertyName){
	std::vector<Property<std::string, std::string>>::iterator iter;

	std::string _val; 

	for (iter = this->properties.begin(); iter != this->properties.end(); ++iter){
		if (iter->key == PropertyName){
			_val = iter->value;
			break; 
		}
	}

	// Create a string iterator 
	std::string::reverse_iterator it;
	U32 _multiplier = 1; 
	S32 _return = 0; //!< value to return 

	for (it = _val.rbegin(); it != _val.rend(); ++it){
		_return += ( (*it)-48) * _multiplier;
		_multiplier *= 10;
	}

	return _return; 
}