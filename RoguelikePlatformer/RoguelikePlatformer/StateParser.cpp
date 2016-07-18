#include "StateParser.h"
#include "GameManager.h"
#include "TextureManager.h"
#include "ObjectFactory.h"

bool StateParser::ParseState(const char * stateFile, std::string stateId, std::vector<Object*>* pvObject, std::vector<std::string> *pvTextureId)
{
	tinyxml2::XMLDocument xmlDoc;

	if (xmlDoc.LoadFile(stateFile) !=tinyxml2::XML_SUCCESS)
	{
		std::cerr << "XML File Load Error.\n";
		return false;
	}

	tinyxml2::XMLElement *pRoot = xmlDoc.RootElement();
	tinyxml2::XMLElement *pState, *pObject, *pTexture;

	pState = pRoot->FirstChildElement(stateId.c_str());
	pTexture = pState->FirstChildElement("TEXTURES");
	pObject = pState->FirstChildElement("OBJECTS");

	ParseTexture(pTexture, pvTextureId);
	ParseObject(pObject, pvObject);

	return true;
}

void StateParser::ParseObject(tinyxml2::XMLElement * pRoot, std::vector<Object*>* pvObject)
{
	std::string textureId, motionType;
	int x, y, width, height, scale, frame, callbackId;

	for (tinyxml2::XMLElement *pe = pRoot->FirstChildElement(); pe != NULL; pe = pe->NextSiblingElement())
	{
		x = pe->IntAttribute("x");
		y = pe->IntAttribute("y");
		width = pe->IntAttribute("width");
		height = pe->IntAttribute("height");
		scale = pe->IntAttribute("scale");
		frame = pe->IntAttribute("frame");
		callbackId = pe->IntAttribute("callbackId");

		textureId = pe->Attribute("textureId");

		if( pe->Attribute("motionType")) motionType = pe->Attribute("motionType");
		int imt=0;

		if (motionType == "REPEAT")
			imt = REPEAT;
		else if (motionType == "RANDOM")
			imt = RANDOM;
		else
			imt = NONE;

		Object *pObject = ObjectFactory::Instance()->Create(pe->Attribute("type"));
		pObject->Load(new LoaderParameter(x, y, width, height, scale, textureId, callbackId, imt));
		pvObject->push_back(pObject);

		//TextureManager::Instance()->Load(pe->Attribute("filename"), pe->Attribute("id"), GameManager::Instance()->GetRenderer());
	}
}

void StateParser::ParseTexture(tinyxml2::XMLElement * pRoot, std::vector<std::string>* pvTextureId)
{
	for (tinyxml2::XMLElement *pe = pRoot->FirstChildElement(); pe != NULL; pe = pe->NextSiblingElement())
	{
		TextureManager::Instance()->Load(pe->Attribute("filename"), pe->Attribute("id"), GameManager::Instance()->GetRenderer());
	}
}
