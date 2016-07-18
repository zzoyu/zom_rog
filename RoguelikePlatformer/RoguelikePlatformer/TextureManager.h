#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <map>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
private:
	std::map< std::string, SDL_Texture * > m_mapTexture;
	TextureManager(){}
	~TextureManager(){}

	static TextureManager * s_pInstance;

public:

	static TextureManager * Instance()
	{
		if( s_pInstance == 0 )
			s_pInstance = new TextureManager();

		return s_pInstance;
	}

	bool Load( std::string _sFileName, std::string _sId, SDL_Renderer* _pRenderer );

	void Clear( std::string _sId );

	void Draw( std::string _sId, int _iX, int _iY, int _iW, int _iH, int _iScale, SDL_Renderer* _pRenderer, SDL_RendererFlip _flip = SDL_FLIP_NONE );

	void DrawFrame(std::string _sId, int _iX, int _iY, int _iW, int _iH, int _iScale, int _iCurrentRow, int _iCurrentFrame, SDL_Renderer * _pRenderer, SDL_RendererFlip _flip = SDL_FLIP_NONE)

	{
		SDL_Rect	m_stRectSrc, m_stRectDest;

		m_stRectDest.x = _iX;
		m_stRectDest.y = _iY;
		m_stRectSrc.x = _iW * _iCurrentFrame;
		m_stRectSrc.y = _iH * _iCurrentRow;

		m_stRectSrc.h = _iH;
		m_stRectSrc.w = _iW;

		m_stRectDest.h = m_stRectSrc.h * _iScale;
		m_stRectDest.w = m_stRectSrc.w * _iScale;

		SDL_RenderCopyEx(_pRenderer, m_mapTexture[_sId], &m_stRectSrc, &m_stRectDest, NULL, NULL, _flip);
	}

	//void DrawFrame( std::string _sId, int _iX, int _iY, int _iW, int _iH, int _iScale, int _iCurrentRow, int _iCurrentFrame, SDL_Renderer* _pRenderer, SDL_RendererFlip _flip = SDL_FLIP_NONE );

	int GetRow( std::string _sId, int _iFrameHeight )
	{
		int iW, iH;

		SDL_QueryTexture( m_mapTexture[_sId], NULL, NULL, &iW, &iH );

		return( iH/_iFrameHeight );
	}

	int GetFrame(std::string _sId, int _iFrameWidth)
	{
		int iW, iH;

		SDL_QueryTexture(m_mapTexture[_sId], NULL, NULL, &iW, &iH);

		return(iW / _iFrameWidth);
	}
};

#endif