#include "TextureManager.h"

TextureManager * TextureManager::s_pInstance = 0;

bool TextureManager::Load( std::string _sFileName, std::string _sId, SDL_Renderer* _pRenderer )
{
	SDL_Surface * m_pSurface = IMG_Load( _sFileName.c_str() );

	if( m_pSurface == 0 ) return false;

	m_mapTexture[_sId] = SDL_CreateTextureFromSurface( _pRenderer, m_pSurface );

	SDL_FreeSurface( m_pSurface );

	if( m_mapTexture[_sId] ) return true;
	else return false;
}

void TextureManager::Clear( std::string _sId )
{
	SDL_DestroyTexture( m_mapTexture[_sId] );
	m_mapTexture.erase(_sId);
}

void TextureManager::Draw( std::string _sId, int _iX, int _iY, int _iW, int _iH, int _iScale, SDL_Renderer* _pRenderer, SDL_RendererFlip _flip )
{
	SDL_Rect	m_stRectSrc, m_stRectDest;

	m_stRectDest.x = _iX;
	m_stRectDest.y = _iY;
	m_stRectSrc.x = 0;
	m_stRectSrc.y = 0;

	m_stRectDest.h = _iScale * (m_stRectSrc.h = _iH);
	m_stRectDest.w = _iScale * (m_stRectSrc.w = _iW);

	SDL_RenderCopyEx( _pRenderer, m_mapTexture[_sId], &m_stRectSrc, &m_stRectDest, NULL, NULL, _flip );
}

