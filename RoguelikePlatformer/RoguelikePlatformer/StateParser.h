#pragma once

#include <iostream>
#include <vector>

#include "tinyxml2\tinyxml2.h"

class Object;

class StateParser
{
public:
	bool ParseState(const char* stateFile, std::string stateId, std::vector<Object*> *pvObject, std::vector<std::string> *pvTextureId);
private:
	void ParseObject(tinyxml2::XMLElement *pStateRoot, std::vector<Object*> *pvObject);
	void ParseTexture(tinyxml2::XMLElement *pStateRoot, std::vector<std::string> *pvTextureId);
};