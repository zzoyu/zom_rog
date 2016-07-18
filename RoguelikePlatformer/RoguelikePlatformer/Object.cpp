#include "Object.h"

#include "GameManager.h"
#include "TextureManager.h"

SDLObject::SDLObject( const LoaderParameter * pParam ) : Object( pParam ), m_vPosition( (float)(pParam->GetXPos()), (float)(pParam->GetYPos()) ), m_vVelocity( (float)0, (float)0 ), m_vAcceleration( (float)0, (float)0 )
{
	m_iW = pParam->GetWidth();
	m_iH = pParam->GetHeight();
	m_iScale = pParam->GetScale();
	m_sId = pParam->GetTextureID();

	m_iCurrentFrame = 0;
	m_iCurrentRow = 0;

	m_bDirection = true;
}


void SDLObject::Load(const LoaderParameter *_pParam)
{
	m_vPosition = Vector2D(_pParam->GetXPos(), _pParam->GetYPos());
	m_vVelocity = Vector2D(0, 0);
	m_vAcceleration = Vector2D(0, 0);
	m_iW = _pParam->GetWidth();
	m_iH = _pParam->GetHeight();
	m_sId = _pParam->GetTextureID();
	m_iCurrentRow = 0;
	m_iCurrentFrame = 0;
	m_iTotalFrame = _pParam->GetTotalFrame();
	m_iScale = _pParam->GetScale();

	m_bDirection = true;
}

void SDLObject::Draw()
{
	if( m_bDirection )
		TextureManager::Instance()->DrawFrame( m_sId, (int)(m_vPosition.GetX()), (int)(m_vPosition.GetY()), m_iW, m_iH, m_iScale, m_iCurrentRow, m_iCurrentFrame, GameManager::Instance()->GetRenderer() );
	else
		TextureManager::Instance()->DrawFrame( m_sId, (int)(m_vPosition.GetX()), (int)(m_vPosition.GetY()), m_iW, m_iH, m_iScale, m_iCurrentRow, m_iCurrentFrame, GameManager::Instance()->GetRenderer(), SDL_FLIP_HORIZONTAL );
}

void SDLObject::Update()
{
	m_vVelocity += m_vAcceleration;
	m_vPosition += m_vVelocity;

	if (m_iCurrentFrame >= m_iTotalFrame)
		m_iCurrentFrame = 0;
}

void SDLObject::Clean()
{
}

Player::Player( const LoaderParameter * pParam ) : SDLObject( pParam ){}

void Player::Draw()
{
	SDLObject::Draw();
}

void Player::Update()
{
	m_iCurrentFrame = ( SDL_GetTicks() / 100 ) % 4;

	m_vVelocity.SetX( 0 );
	m_vVelocity.SetY( 0 );

	HandleInput();

	SDLObject::Update();
}

void Player::Clean()
{
	
}

void Player::Load(const LoaderParameter * pParam)
{
	SDLObject::Load(pParam);
}

void Player::HandleInput()
{
	float fValue;

	fValue = InputHandler::Instance()->XValue( 0, 1 );
	if( fValue > 0 || fValue < 0 )
	{
		m_vVelocity.SetX( 1 * fValue );
		m_bDirection = true;
	}

	fValue = InputHandler::Instance()->YValue( 0, 1 );
	if( fValue > 0 || fValue < 0 )
		m_vVelocity.SetY( 1 * fValue );

	fValue = InputHandler::Instance()->XValue( 0, 2 );
	if( fValue > 0 || fValue < 0 )
	{
		m_vVelocity.SetX( 1 * fValue );
		m_bDirection = false;
	}

	fValue = InputHandler::Instance()->YValue( 0, 2 );
	if( fValue > 0 || fValue < 0 )
		m_vVelocity.SetY( 1 * fValue );

	if( InputHandler::Instance()->GetKeyState( SDL_SCANCODE_RIGHT ) )
	{
		m_vVelocity.SetX(1);
		m_bDirection = true;
	}
	if( InputHandler::Instance()->GetKeyState( SDL_SCANCODE_LEFT ) )
	{
		m_vVelocity.SetX(-1);
		m_bDirection = false;
	}

	if( InputHandler::Instance()->GetKeyState( SDL_SCANCODE_UP ) )
		m_vVelocity.SetY(-1);
	if( InputHandler::Instance()->GetKeyState( SDL_SCANCODE_DOWN ) )
		m_vVelocity.SetY(1);
}

//Enemy( const LoaderParameter * pParam ) : SDLObject( pParam ){}

void Enemy::Load(const LoaderParameter * pParam)
{
	SDLObject::Load(pParam);
}

void Enemy::Draw()
{
	SDLObject::Draw();
}

void Enemy::Update()
{
	if( m_vPosition.GetX() <= 0 )
		m_vVelocity.SetX(-1);
	else
		m_vVelocity.SetX(1);
	m_vPosition.SetX( m_vPosition.GetX() + m_vVelocity.GetX() );
	m_iCurrentFrame = ( SDL_GetTicks() / 100 ) % 4;
}

void Enemy::Clean()
{
	
}
/*
GUIImage::GUIImage( const LoaderParameter * pParam, int _iMotion, Vector2D _vMotion ) : SDLObject( pParam ), m_iMotion(_iMotion), m_vMotion(_vMotion)
{
	srand( SDL_GetTicks() );
	m_vOriginal = m_vPosition;
	//m_vVelocity.SetX(1);
	m_iCurrentRow = rand()%TextureManager::Instance()->GetRow(m_sId,32);
}
*/

void GUIImage::Load(const LoaderParameter * pParam)
{
	SDLObject::Load(pParam);

	m_iMotion = pParam->GetMotion();
	m_vMotion = Vector2D(0, 0);
	srand(SDL_GetTicks());
	m_vOriginal = m_vPosition;
	//m_vVelocity.SetX(1);
	m_iCurrentRow = rand() % TextureManager::Instance()->GetRow(m_sId, 32);
}

void GUIImage::Draw()
{
	SDLObject::Draw();
}

void GUIImage::Update()
{
	m_iCurrentFrame = ( SDL_GetTicks() / 100 ) % 4;
	//m_iCurrentFrame = 0;

	//if (m_iCurrentFrame >= m_iTotalFrame)m_iCurrentFrame = 0;

	int iRandom;

	if (m_iCurrentFrame == 0)
	{
		switch (m_iMotion)
		{
		case REPEAT:
			if (abs(m_vPosition.GetX() - m_vOriginal.GetX())
				>=
				abs(m_vMotion.GetX())
				)
				m_vVelocity.SetX(-m_vVelocity.GetX());
			break;
		case RANDOM:
			iRandom = rand() % 3;
			switch (iRandom)
			{
			case 0:
				m_vVelocity.SetX(-1);
				break;
			case 1:
				m_vVelocity.SetX(0);
				break;
			case 2:
				m_vVelocity.SetX(1);
				break;
			}

			iRandom = rand() % 3;
			switch (iRandom)
			{
			case 0:
				m_vVelocity.SetY(-1);
				break;
			case 1:
				m_vVelocity.SetY(0);
				break;
			case 2:
				m_vVelocity.SetY(1);
				break;
			}
			break;
		default:
			m_iCurrentFrame = 0;
			break;
		}
	}
	SDLObject::Update();
}

void GUIImage::Clean()
{
	
}