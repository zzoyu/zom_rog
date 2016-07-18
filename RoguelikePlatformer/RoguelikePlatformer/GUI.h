#ifndef	__GUI_H__
#define	__GUI_H__

#include "Object.h"

enum BUTTON_STATE
{
	IDLE,
	HOVER
};

class GUIButton : public SDLObject
{
public:
	GUIButton() : SDLObject() {}

	void Load(const LoaderParameter *pParam);
	/*GUIButton(const LoaderParameter *pParam) : SDLObject(pParam)
	{}*/

	void SetCallback(void(*fp)())
	{
		m_fpCallback = fp;
	}

	int GetCallbackId()
	{
		return m_iCallback;
	}

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	static void MenuToPlay();
	static void MenuToQuit();

private:
	void (*m_fpCallback)();
	int m_iCallback;

	bool m_bReleased;
};

#endif