#include "GameManager.h"

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main( int argc, char* args[] )
{	
	Uint32 m_iFrameStart, m_iFrameTime;

	if( GameManager::Instance()->Init(
		"Zombie!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 320, SDL_WINDOW_SHOWN
		) == false )	return -1;

	while( GameManager::Instance()->IsRunning() )
	{
		m_iFrameStart = SDL_GetTicks();

		GameManager::Instance()->HandleEvent();
		GameManager::Instance()->Update();
		GameManager::Instance()->Render();

		m_iFrameTime = SDL_GetTicks() - m_iFrameStart;

		if( m_iFrameTime < DELAY_TIME )
			SDL_Delay( DELAY_TIME - m_iFrameTime );
	}

	GameManager::Instance()->Clean();

	return 0;
}