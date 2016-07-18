#include "GameState.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "StateParser.h"
#include "GUI.h"

const std::string MenuState::s_sMenuID = "MENU";
const std::string PlayState::s_sPlayID = "PLAY";
const std::string PauseState::s_sPauseID = "PAUSE";
const std::string GameOverState::s_sGameOverID = "GAMEOVER";

void MenuState::Update()
{
	for( int i=0; i<m_vObject.size(); i++ )
	{
		if( !m_vObject.empty() )
			m_vObject[i]->Update();
	}
}

void MenuState::Render()
{
	//SDL_SetRenderDrawColor( GameManager::Instance()->GetRenderer(), 240, 240, 240, 255 );
	//SDL_RenderClear( GameManager::Instance()->GetRenderer() );

	for( int i=0; i<m_vObject.size(); i++ )
	{
		m_vObject[i]->Draw();
	}
}

bool MenuState::OnEnter()
{
	std::cout << "Now Entering Menu..." << std::endl;
	/*
	if( !TextureManager::Instance()->Load(
		"./res/img/start.png", "ui/button/start", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}
	if( !TextureManager::Instance()->Load(
		"./res/img/quit.png", "ui/button/quit", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}
	if( !TextureManager::Instance()->Load(
		"./res/img/title_text.png", "ui/title/text", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}

	if( !TextureManager::Instance()->Load(
		"./res/img/char_zombie.png", "char/zombie", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}
	*/

	StateParser m_parser;

	m_parser.ParseState("state.xml", GetStateID(), &m_vObject, NULL);

	m_vCallback.push_back(GUIButton::MenuToPlay);
	m_vCallback.push_back(GUIButton::MenuToQuit);

	SetCallback(m_vCallback);

	//Object * pButtonStart = new GUIButton( new LoaderParameter( 100, 200, 105, 29, 1, "ui/button/start" ), GUIButton::MenuToPlay );
	//Object * pButtonQuit = new GUIButton( new LoaderParameter( 100, 240, 105, 29, 1, "ui/button/quit" ), GUIButton::MenuToQuit );

	//Object * pBackground = new SDLObject( new LoaderParameter( 0, 0, 720, 320, 1, "ui/title/text" ) );
	//Object * pImg = new GUIImage( new LoaderParameter( 100, -300, 32, 32, 24, "char/zombie" ), RANDOM );
	//Object * pImg = new GUIImage( new LoaderParameter( 0, 0, 90, 115, "ui/title/zombie" ), RANDOM );

	/*m_vObject.push_back( pImg );
	m_vObject.push_back( pBackground );
	m_vObject.push_back( pButtonStart );
	m_vObject.push_back( pButtonQuit );
	*/
	return true;
}

bool MenuState::OnExit()
{
	std::cout << "Now Exiting Menu..." << std::endl;

	for( int i=0; i<m_vObject.size(); i++ )
	{
		m_vObject[i]->Clean();
	}
	m_vObject.clear();

	TextureManager::Instance()->Clear( "ui/button/start" );
	TextureManager::Instance()->Clear( "ui/button/quit" );
	TextureManager::Instance()->Clear( "ui/title/text" );
	TextureManager::Instance()->Clear( "char/zombie" );

	return true;
}

void MenuState::SetCallback(std::vector<void(*)()>& vCallback)
{
	for (int i = 0; i < m_vObject.size(); i++)
		if (dynamic_cast<GUIButton*>(m_vObject[i]))
		{
			GUIButton *p = dynamic_cast<GUIButton*>(m_vObject[i]);
			p->SetCallback(vCallback[p->GetCallbackId()]);
		}
}

void PlayState::Update()
{
	if( InputHandler::Instance()->GetKeyState( SDL_SCANCODE_ESCAPE ) )
		GameManager::Instance()->GetGameStateMachine()->PushState( new PauseState() );
	for( int i=0; i<m_vObject.size(); i++ )
		m_vObject[i]->Update();

	if( CheckCollision( dynamic_cast<SDLObject*>(m_vObject[0]), dynamic_cast<SDLObject*>(m_vObject[1]) ) )
	{
		GameManager::Instance()->GetGameStateMachine()->PushState( new GameOverState() );
	}
}

void PlayState::Render()
{
	for( int i=0; i<m_vObject.size(); i++ )
		m_vObject[i]->Draw();
}

bool PlayState::OnEnter()
{
	std::cout << "Now Entering Play State..." << std::endl;
	/*
	if( !TextureManager::Instance()->Load( "./res/img/character.png", "char/player", GameManager::Instance()->GetRenderer() ) )
		return false;
	if( !TextureManager::Instance()->Load( "./res/img/effect_damaged.png", "effect/dam", GameManager::Instance()->GetRenderer() ) )
		return false;

	if( !TextureManager::Instance()->Load( "./res/img/char_zombie.png", "char/zombie", GameManager::Instance()->GetRenderer() ) )
		return false;

	m_vObject.push_back( new Player( new LoaderParameter( 300, 50, 32, 32, 1, "char/player" ) ) );
	m_vObject.push_back( new Enemy( new LoaderParameter( 50, 100, 32, 32, 1, "char/zombie" ) ) );
	*/
	return true;
}

bool PlayState::OnExit()
{
	std::cout << "Now Exiting Play State..." << std::endl;

	for( int i=0; i<m_vObject.size(); i++ )
		m_vObject[i]->Clean();
	m_vObject.clear();

	TextureManager::Instance()->Clear( "char/player" );
	TextureManager::Instance()->Clear( "char/zombie" );
	TextureManager::Instance()->Clear( "effect/dam" );

	return true;
}

bool PlayState::CheckCollision( SDLObject *_pObject1, SDLObject *_pObject2 )
{
	if( 
		(_pObject1->GetPosition()->GetX()+_pObject1->GetWidth()) < (_pObject2->GetPosition()->GetX()) ||
		(_pObject1->GetPosition()->GetY()+_pObject1->GetHeight()) < (_pObject2->GetPosition()->GetY()) ||
		(_pObject1->GetPosition()->GetX() > (_pObject2->GetPosition()->GetX()+_pObject2->GetWidth())) ||
		(_pObject1->GetPosition()->GetY() > (_pObject2->GetPosition()->GetY()+_pObject2->GetHeight()))
		)
	{
		return false;
	}
	else
		return true;
}

void PauseState::PauseToMain()
{
	GameManager::Instance()->GetGameStateMachine()->ChangeState( new MenuState() );
	InputHandler::Instance()->ResetMouseState();
}

void PauseState::PauseToPlay()
{
	GameManager::Instance()->GetGameStateMachine()->PopState();
}

void PauseState::Update()
{
	for( int i=0; i<m_vObject.size(); i++ )
	{
		if( !m_vObject.empty() )
			m_vObject[i]->Update();
	}
}

void PauseState::Render()
{
	for( int i=0; i<m_vObject.size(); i++ )
	{
		m_vObject[i]->Draw();
	}
}

bool PauseState::OnEnter()
{
	std::cout << "Now Entering PauseState..." << std::endl;

	if( !TextureManager::Instance()->Load(
		"./res/img/resume.png", "button_resume", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}
	if( !TextureManager::Instance()->Load(
		"./res/img/menu.png", "button_menu", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}

	//SDLObject * pButtonResume = new GUIButton( new LoaderParameter( 100, 200, 105, 29, 1, "button_resume" ), PauseToPlay );
	//SDLObject * pButtonMenu = new GUIButton( new LoaderParameter( 100, 240, 105, 29, 1, "button_menu" ), PauseToMain );

	//m_vObject.push_back( pButtonResume );
	//m_vObject.push_back( pButtonMenu );

	return true;
}

bool PauseState::OnExit()
{
	std::cout << "Now Exiting PauseState..." << std::endl;

	for( int i=0; i<m_vObject.size(); i++ )
	{
		m_vObject[i]->Clean();
	}
	m_vObject.clear();

	TextureManager::Instance()->Clear( "button_resume" );
	TextureManager::Instance()->Clear( "button_menu" );

	return true;
}

void GameOverState::GameOverToMain()
{
	GameManager::Instance()->GetGameStateMachine()->ChangeState( new MenuState() );
	InputHandler::Instance()->ResetMouseState();
}

void GameOverState::Update()
{
	for( int i=0; i<m_vObject.size(); i++ )
	{
		if( !m_vObject.empty() )
			m_vObject[i]->Update();
	}
}

void GameOverState::Render()
{
	for( int i=0; i<m_vObject.size(); i++ )
	{
		m_vObject[i]->Draw();
	}
}

bool GameOverState::OnEnter()
{
	std::cout << "Now Entering GameOver State..." << std::endl;

	if( !TextureManager::Instance()->Load(
		"./res/img/gameover.png", "ui/gameover/text", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}

	if( !TextureManager::Instance()->Load(
		"./res/img/menu.png", "ui/button/menu", GameManager::Instance()->GetRenderer()
		)
		)
	{
		return false;
	}

/*	SDLObject * pText = new SDLObject( new LoaderParameter( 0, 0, 720, 320, 1, "ui/gameover/text" ) );

	SDLObject * pButtonMenu = new GUIButton( new LoaderParameter( 308, 220, 105, 29, 1, "ui/button/menu" ), GameOverToMain );

	m_vObject.push_back( pText );
	m_vObject.push_back( pButtonMenu );
	*/
	return true;
}

bool GameOverState::OnExit()
{
	std::cout << "Now Exiting GameOverState..." << std::endl;

	for( int i=0; i<m_vObject.size(); i++ )
	{
		m_vObject[i]->Clean();
	}
	m_vObject.clear();

	TextureManager::Instance()->Clear( "ui/gameover/text" );
	TextureManager::Instance()->Clear( "button/menu" );

	return true;
}