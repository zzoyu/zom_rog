#include "InputHandler.h"
#include "GameManager.h"

#include <iostream>

InputHandler * InputHandler::s_pInstance = 0;

void InputHandler::InitJoystick()
{
	if( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 )
		SDL_InitSubSystem( SDL_INIT_JOYSTICK );
	if( SDL_NumJoysticks() > 0 )
	{
		for( int i=0; i<SDL_NumJoysticks(); i++ )
		{
			SDL_Joystick *pJoystick = SDL_JoystickOpen( i );
			if( SDL_JoystickGetAttached( pJoystick ) )
			{
				m_vJoystick.push_back( pJoystick );
				m_vJoystickValue.push_back( std::make_pair( new Vector2D(0,0), new Vector2D(0,0) ) );

				std::vector<bool> vTempButton;

				for( int j=0; j<SDL_JoystickNumButtons(pJoystick); j++ )
					vTempButton.push_back(false);

				m_vButton.push_back( vTempButton );
			}
			else
				std::cout << SDL_GetError();
		}
		SDL_JoystickEventState( SDL_ENABLE );
		m_bIsJSInitialized = true;

		std::cout << "Initialized Joysticks : " << m_vJoystick.size() << std::endl;
	}
	else
		m_bIsJSInitialized = false;

}

void InputHandler::Clean()
{
	if( m_bIsJSInitialized )
		for( unsigned int i=0; i<SDL_NumJoysticks(); i++ )
			SDL_JoystickClose( m_vJoystick[i] );
}

void InputHandler::Update()
{
	SDL_Event stEvent;
	SDL_Surface * _pSurface;

	int iController;

	if( SDL_PollEvent( &stEvent ) )
	{
		switch( stEvent.type )
		{
		case SDL_QUIT:
			GameManager::Instance()->Quit();
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove( stEvent );
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown( stEvent );
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp( stEvent );
			break;
		case SDL_JOYAXISMOTION:
			OnJoystickAxisMove( stEvent );
			break;

		case SDL_JOYBUTTONDOWN:
			OnJoystickButtonDown( stEvent );
			break;
		case SDL_JOYBUTTONUP:
			OnJoystickButtonUp( stEvent );
			break;
		case SDL_KEYDOWN:
			OnKeyDown();
			switch( stEvent.key.keysym.sym )
			{
			case SDLK_F5:
				/*m_pSurface = SDL_GetWindowSurface( m_pWindow );
				IMG_SavePNG( m_pSurface, "screen.png" );
				SDL_FreeSurface( m_pSurface );*/
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			OnKeyUp();
			break;
		default:
			break;
		}
	}
}

void InputHandler::OnKeyDown()
{
	m_pKeyState = (Uint8*)SDL_GetKeyboardState(0);
}
void InputHandler::OnKeyUp()
{
	m_pKeyState = (Uint8*)SDL_GetKeyboardState(0);
}

void InputHandler::OnMouseMove(SDL_Event& _stEvent)
{
	m_vMousePosition.SetX( _stEvent.motion.x );
	m_vMousePosition.SetY( _stEvent.motion.y );
}

void InputHandler::OnMouseButtonDown(SDL_Event& _stEvent)
{
	switch( _stEvent.button.button )
	{
	case SDL_BUTTON_LEFT:
		m_vMouse[LEFT] = true;
		break;
	case SDL_BUTTON_MIDDLE:
		m_vMouse[MIDDLE] = true;
		break;
	case SDL_BUTTON_RIGHT:
		m_vMouse[RIGHT] = true;
		break;
	default:
		break;
	}
}

void InputHandler::OnMouseButtonUp(SDL_Event& _stEvent)
{
	switch( _stEvent.button.button )
	{
	case SDL_BUTTON_LEFT:
		m_vMouse[LEFT] = false;
		break;
	case SDL_BUTTON_MIDDLE:
		m_vMouse[MIDDLE] = false;
		break;
	case SDL_BUTTON_RIGHT:
		m_vMouse[RIGHT] = false;
		break;
	default:
		break;
	}
}

void InputHandler::OnJoystickAxisMove(SDL_Event& _stEvent)
{
	if( _stEvent.jaxis.axis == 0 )
	{
		if( _stEvent.jaxis.value > m_iJoystickDeadZone )
			m_vJoystickValue[_stEvent.jaxis.which].first->SetX( 1 );
		else if( _stEvent.jaxis.value < -m_iJoystickDeadZone )
			m_vJoystickValue[_stEvent.jaxis.which].first->SetX( -1 );
		else
			m_vJoystickValue[_stEvent.jaxis.which].first->SetX( 0 );
	}
	/*
	if( stEvent.jaxis.axis == 1 )
	{
		if( stEvent.jaxis.value > m_iJoystickDeadZone )
			m_vJoystickValue[iController].first->SetY( 1 );
		else if( stEvent.jaxis.value < -m_iJoystickDeadZone )
			m_vJoystickValue[iController].first->SetY( -1 );
		else
			m_vJoystickValue[iController].first->SetY( 0 );
	}
			
	if( stEvent.jaxis.axis == 3 )
	{
		if( stEvent.jaxis.value > m_iJoystickDeadZone )
			m_vJoystickValue[iController].second->SetX( 1 );
		else if( stEvent.jaxis.value < -m_iJoystickDeadZone )
			m_vJoystickValue[iController].second->SetX( -1 );
		else
			m_vJoystickValue[iController].second->SetX( 0 );
	}*/

	if( _stEvent.jaxis.axis == 4 )
	{
		if( _stEvent.jaxis.value > m_iJoystickDeadZone )
			m_vJoystickValue[_stEvent.jaxis.which].second->SetY( 1 );
		else if( _stEvent.jaxis.value < -m_iJoystickDeadZone )
			m_vJoystickValue[_stEvent.jaxis.which].second->SetY( -1 );
		else
			m_vJoystickValue[_stEvent.jaxis.which].second->SetY( 0 );
	}
}

void InputHandler::OnJoystickButtonDown(SDL_Event& _stEvent)
{
	m_vButton[_stEvent.jaxis.which][_stEvent.jbutton.button] = true;
}

void InputHandler::OnJoystickButtonUp(SDL_Event& _stEvent)
{
	m_vButton[_stEvent.jaxis.which][_stEvent.jbutton.button] = false;
}