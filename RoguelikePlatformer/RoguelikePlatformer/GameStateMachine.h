#ifndef __GAME_STATE_MACHINE_H__
#define __GAME_STATE_MACHINE_H__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void PushState( GameState *_pState );
	void ChangeState( GameState * _pState );
	void PopState();

	void Update();
	void Render();

private:
	std::vector<GameState *> m_vGameState;
};

#endif