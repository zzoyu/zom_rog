#include "GUI.h"
#include "GameManager.h"
#include <iostream>
/*
GUIButton::GUIButton( const LoaderParameter *pParam ) : SDLObject( pParam )
{
	m_iCurrentFrame = IDLE;
	m_iCallback = pParam->GetCallbackId();
	m_bReleased = true;
}/**/

void GUIButton::Load(const LoaderParameter * pParam)
{
	SDLObject::Load(pParam);

	m_iCurrentFrame = IDLE;
	m_iCallback = pParam->GetCallbackId();
	m_bReleased = true;
}

void GUIButton::Draw()
{
	SDLObject::Draw();
}

void GUIButton::Update()
{
	Vector2D *pMousePos = InputHandler::Instance()->GetMousePosition();

	if( pMousePos->GetX() > m_vPosition.GetX() &&
		pMousePos->GetX() < ( m_vPosition.GetX() + m_iW ) &&
		pMousePos->GetY() > m_vPosition.GetY() &&
		pMousePos->GetY() < ( m_vPosition.GetY() + m_iH ) )
	{
		m_iCurrentFrame = HOVER;

		if( InputHandler::Instance()->GetMouseState( LEFT ) )
		{
			if( m_bReleased )
			{
				m_fpCallback();
				m_bReleased = false;
			}
		}
		else
			m_bReleased = true;

		//std::cout << "Hover!\n" << std::endl;
	}
	else
		m_iCurrentFrame = IDLE;
}

void GUIButton::Clean()
{
	SDLObject::Clean();
}

void GUIButton::MenuToPlay()
{
	std::cout << "Play!\n" << std::endl;

	GameManager::Instance()->GetGameStateMachine()->ChangeState( new PlayState() );
}

void GUIButton::MenuToQuit()
{
	std::cout << "Quit!\n" << std::endl;

	GameManager::Instance()->Quit();
}