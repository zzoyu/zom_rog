#ifndef	__GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>
#include "TextureManager.h"
#include "Object.h"
#include "GameStateMachine.h"

class GameManager
{
private:
	bool			m_bGameFlag;
	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;

	int				m_iCurrentFrame;

	static GameManager *s_pInstance;

	GameStateMachine *m_pGameStateMachine;

	GameManager(){}
	~GameManager(){}
public:
	static GameManager* Instance()
	{
		if( s_pInstance == 0 )
		{
			s_pInstance = new GameManager();
		}
		return s_pInstance;
	}

	bool Init( const char * _cpTitle, int _iX, int _iY, int _iW, int _iH, int _iFlag );

	void HandleEvent();

	void Update();

	void Render();

	void Clean();

	void Quit()
	{
		m_bGameFlag = false;
	}

	bool IsRunning();

	SDL_Renderer * GetRenderer() const { return m_pRenderer; }

	GameStateMachine* GetGameStateMachine() { return m_pGameStateMachine; }
};

#endif