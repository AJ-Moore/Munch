
#ifndef __CONFIG_
#define __CONFIG_

#include "Common.h"
#include <vector>


template <class KEY, class VALUE>
class Property{
public:
	/// Constructor property key, value 
	Property(KEY Key, VALUE Val ){
		this->key = Key; 
		this->value = Val; 
	}
	~Property(){}

	/// The property key 
	KEY key; 

	/// The property value
	VALUE value;
};

class Config{
public:
	Config();
	~Config();

	/// Loads the configuration file specified
	void loadConfig(std::string File);

	/// Returns the property 
	std::string getString(std::string PropertyName);

	/// Returns an integer property with the given name.
	S32 getInt(std::string PropertyName);


private:
	/// Holds all the properties loaded by loadConfig( ... )
	std::vector<Property<std::string, std::string>> properties; 

};


#endif
