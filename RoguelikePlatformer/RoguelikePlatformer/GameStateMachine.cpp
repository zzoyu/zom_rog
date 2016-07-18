#include "GameStateMachine.h"

void GameStateMachine::PushState( GameState *_pState )
{
	m_vGameState.push_back( _pState );
	m_vGameState.back()->OnEnter();
}

void GameStateMachine::ChangeState( GameState *_pState )
{
	if( !m_vGameState.empty() )
	{
		if( m_vGameState.back()->GetStateID() == _pState->GetStateID() )
			return;
		if( m_vGameState.back()->OnExit() )
		{
			m_vGameState.pop_back();
		}
	}

	m_vGameState.push_back( _pState );
	m_vGameState.back()->OnEnter();
}

void GameStateMachine::PopState()
{
	if( !m_vGameState.empty() )
	{
		if( m_vGameState.back()->OnExit() )
		{
			delete m_vGameState.back();
			m_vGameState.pop_back();
		}
	}
}

void GameStateMachine::Update()
{
	if( !m_vGameState.empty() )
	{
		m_vGameState.back()->Update();
	}
}

void GameStateMachine::Render()
{
	if( !m_vGameState.empty() )
	{
		m_vGameState.back()->Render();
	}
}