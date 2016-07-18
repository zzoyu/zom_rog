#pragma once

#ifndef	__OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__

#include <string>
#include <map>

#include "Object.h"
#include "GUI.h"

class BaseCreator
{
public:
	virtual Object* CreateObject()	const = 0;
	virtual ~BaseCreator() {};
};

class PlayerCreator : public BaseCreator
{
	Object * CreateObject() const
	{
		return new Player();
	}
};

class EnemyCreator : public BaseCreator
{
	Object * CreateObject() const
	{
		return new Enemy();
	}
};

class GUIImageCreator : public BaseCreator
{
	Object * CreateObject() const
	{
		return new GUIImage();
	}
};

class GUIButtonCreator : public BaseCreator
{
	Object * CreateObject() const
	{
		return new GUIButton();
	}
};

class ObjectFactory
{
private:
	std::map<std::string, BaseCreator*> m_mapCreator;
	static ObjectFactory *m_instance;
public:
	static ObjectFactory* Instance()
	{
		if (m_instance == NULL)
			m_instance = new ObjectFactory();
		return m_instance;
	}

	bool RegisterType(std::string _typeID, BaseCreator* _pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_mapCreator.find(_typeID);

		// If already exists
		if (it != m_mapCreator.end())
		{
			delete _pCreator;
			return false;
		}

		m_mapCreator[_typeID] = _pCreator;
		return true;
	}

	Object *Create(std::string _typeId)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_mapCreator.find(_typeId);

		if (it == m_mapCreator.end())
		{
			return NULL;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->CreateObject();
	}
};
#endif
