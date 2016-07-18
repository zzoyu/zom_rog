#include "GameManager.h"
#include "ObjectFactory.h"
#include "InputHandler.h"

GameManager * GameManager::s_pInstance = 0;

bool GameManager::Init( const char * _cpTitle, int _iX, int _iY, int _iW, int _iH, int _iFlag )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		return false;

	m_pWindow = SDL_CreateWindow(
		_cpTitle, _iX, _iY, _iW, _iH, _iFlag );

	if( m_pWindow == 0 )
		return false;
	
	m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, 0 );

	if( m_pRenderer == 0 )
		return false;

	m_bGameFlag = true;

	InputHandler::Instance()->InitJoystick();

	ObjectFactory::Instance()->RegisterType("button", new GUIButtonCreator());
	ObjectFactory::Instance()->RegisterType("image", new GUIImageCreator());
	ObjectFactory::Instance()->RegisterType("player", new PlayerCreator());
	ObjectFactory::Instance()->RegisterType("enemy", new EnemyCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->ChangeState( new MenuState() );

	return true;
}

void GameManager::HandleEvent()
{
	InputHandler::Instance()->Update();

	if( InputHandler::Instance()->GetKeyState( SDL_SCANCODE_RETURN ) )
	{
		m_pGameStateMachine->ChangeState( new PlayState() );
	}
}

void GameManager::Update()
{
	m_iCurrentFrame = ( SDL_GetTicks() / 100 ) % 4;
	
	m_pGameStateMachine->Update();
}

void GameManager::Render()
{
	SDL_SetRenderDrawColor( m_pRenderer, 33, 33, 33, 255 );

	SDL_RenderClear( m_pRenderer );

	m_pGameStateMachine->Render();

	SDL_RenderPresent( m_pRenderer );
}

void GameManager::Clean()
{
	InputHandler::Instance()->Clean();

	SDL_DestroyRenderer( m_pRenderer );
	SDL_DestroyWindow( m_pWindow );

	SDL_Quit();
}

bool GameManager::IsRunning()
{
	return m_bGameFlag;
}