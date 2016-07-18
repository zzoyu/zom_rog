#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <iostream>

#include "Object.h"

class GameState
{
public:
	virtual void Update()=0;
	virtual void Render()=0;

	virtual bool OnEnter()=0;
	virtual bool OnExit()=0;

	virtual std::string GetStateID() const = 0;
};

class MenuState : public GameState
{
public:

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const
	{
		return s_sMenuID;
	}

private:
	static const std::string s_sMenuID;

	std::vector<Object*> m_vObject;

	virtual void SetCallback(std::vector<void(*)()> &vCallback);
	std::vector< void(*)()> m_vCallback;
};

class PlayState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const
	{
		return s_sPlayID;
	}

	bool CheckCollision( SDLObject *_pObject1, SDLObject *_pObejct2 );

private:
	static const std::string s_sPlayID;

	std::vector<Object*> m_vObject;
};

class PauseState : public PlayState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const
	{
		return s_sPauseID;
	}

private:
	static const std::string s_sPauseID;

	static void PauseToMain();
	static void PauseToPlay();

	std::vector<Object*> m_vObject;
};

class GameOverState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const
	{
		return s_sGameOverID;
	}

private:
	static const std::string s_sGameOverID;

	static void GameOverToMain();

	std::vector<Object*> m_vObject;
};

#endif