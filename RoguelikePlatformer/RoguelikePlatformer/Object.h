#ifndef	__OBJECT_H__
#define	__OBJECT_H__

#include <string>
#include <SDL.h>

#include "Vector2D.h"
#include "InputHandler.h"
#include "TextureManager.h"

class LoaderParameter
{
public:
	LoaderParameter( int _iX, int _iY, int _iW, int _iH, int _iScale, std::string _sId, int _iCallbackId=0, int _iMotionType = 0) : m_iX(_iX), m_iY(_iY), m_iW(_iW), m_iH(_iH), m_iScale(_iScale), m_strTexture(_sId), m_iCallbackId(_iCallbackId), m_iMotionType(_iMotionType)
	{
		m_iFrame = TextureManager::Instance()->GetFrame(m_strTexture, m_iW);
	}

	int GetXPos() const { return m_iX; }
	int GetYPos() const { return m_iY; }

	int GetWidth() const { return m_iW; }
	int GetHeight() const { return m_iH; }
	int GetScale() const { return m_iScale; }

	std::string GetTextureID() const { return m_strTexture; }

	int GetTotalFrame() const { return m_iFrame; }

	int GetCallbackId() const { return m_iCallbackId; }

	int GetMotion() const { return m_iMotionType; }

private:
	int m_iX, m_iY, m_iW, m_iH, m_iScale, m_iFrame;
	std::string m_strTexture;
	int m_iCallbackId, m_iMotionType;
};

class Object
{
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;

	virtual void Load(const LoaderParameter *_pParam) = 0;

protected:
	Object( const LoaderParameter *pParam ){}
	Object() {}
	virtual ~Object(){}
};


class SDLObject : public Object
{
public:
	SDLObject( const LoaderParameter * pParam );
	SDLObject() :Object()
	{

	}

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void Load(const LoaderParameter *_pParam);

	Vector2D *GetPosition()
	{
		return &m_vPosition;
	}

	int GetWidth()
	{
		return m_iW*m_iScale;
	}

	int GetHeight()
	{
		return m_iH*m_iScale;
	}

protected:
	Vector2D m_vPosition, m_vVelocity, m_vAcceleration;
	int m_iW, m_iH, m_iScale;
	int m_iCurrentFrame, m_iCurrentRow, m_iTotalFrame;
	std::string m_sId;

	bool m_bDirection;
};

class Player : public SDLObject
{
public:
	Player( const LoaderParameter * pParam );
	Player::Player() : SDLObject()
	{

	}

	virtual void Draw();

	virtual void Update();

	virtual void Clean();

	virtual void Load( const LoaderParameter *pParam );

private:
	void HandleInput();
};

class Enemy : public SDLObject
{
public:
	//Enemy( const LoaderParameter * pParam );
	Enemy() : SDLObject() {}

	virtual void Load(const LoaderParameter *pParam);

	virtual void Draw();

	virtual void Update();

	virtual void Clean();
};

enum IMAGE_MOTION
{
	NONE,
	REPEAT,
	RANDOM
};

class GUIImage : public SDLObject
{
public:
	GUIImage(){}

	virtual void Load(const LoaderParameter * pParam);
	//GUIImage( const LoaderParameter * pParam, int _iMotion = NONE, Vector2D _vMotion=Vector2D(0,0) );

	virtual void Draw();

	virtual void Update();

	virtual void Clean();

private:
	int m_iMotion;

	Vector2D m_vOriginal, m_vMotion;
};

#endif