#ifndef	__INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <SDL.h>
#include <vector>

#include "Vector2D.h"

const int m_iJoystickDeadZone = 10000;

enum MOUSE_BUTTON
{
	LEFT,
	MIDDLE,
	RIGHT
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if( s_pInstance == 0 )
			s_pInstance = new InputHandler();
		return s_pInstance;
	}

	void Update();
	void Clean();

	void InitJoystick();

	bool IsInitialized(){ return m_bIsJSInitialized; }

	float XValue( int _iJoy, int _iStick )
	{
		if( m_vJoystick.size() > 0 )
		{
			if( _iStick == 1 )
				return m_vJoystickValue[_iJoy].first->GetX();
			else if( _iStick == 2 )
				return m_vJoystickValue[_iJoy].second->GetX();
		}
		return 0;
	}
	float YValue( int _iJoy, int _iStick )
	{
		if( m_vJoystick.size() > 0 )
		{
			if( _iStick == 1 )
				return m_vJoystickValue[_iJoy].first->GetY();
			else if( _iStick == 2 )
				return m_vJoystickValue[_iJoy].second->GetY();
		}
		return 0;
	}

	bool GetButtonState( int _iJoy, int _iButtonNumber )
	{
		return m_vButton[_iJoy][_iButtonNumber];
	}

	bool GetMouseState( int _iButtonNumber )
	{
		return m_vMouse[_iButtonNumber];
	}

	Vector2D *GetMousePosition()
	{
		return &m_vMousePosition;
	}

	bool GetKeyState(SDL_Scancode _key)
	{
		if( m_pKeyState != 0 )
		{
			if( m_pKeyState[_key] == 1 )
				return true;
			else
				return false;
		}
		else
			return false;
	}

	void ResetMouseState()
	{
		m_vMouse[LEFT] = false;
		m_vMouse[MIDDLE] = false;
		m_vMouse[RIGHT] = false;
	}

private:
	InputHandler(){
		m_pKeyState = 0;
		m_vMousePosition = Vector2D(0,0);
		for( int i=0; i<3; i++ )
			m_vMouse.push_back( false );
	}
	~InputHandler(){}

	void OnKeyDown();
	void OnKeyUp();

	void OnMouseMove(SDL_Event& _stEvent);
	void OnMouseButtonDown(SDL_Event& _stEvent);
	void OnMouseButtonUp(SDL_Event& _stEvent);

	void OnJoystickAxisMove(SDL_Event& _stEvent);
	void OnJoystickButtonDown(SDL_Event& _stEvent);
	void OnJoystickButtonUp(SDL_Event& _stEvent);

	static InputHandler *s_pInstance;

	std::vector<SDL_Joystick*> m_vJoystick;
	std::vector<std::vector<bool>> m_vButton;
	std::vector<bool> m_vMouse;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_vJoystickValue;

	Uint8* m_pKeyState;

	bool m_bIsJSInitialized;

	Vector2D m_vMousePosition;
};

#endif