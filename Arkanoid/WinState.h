//WinState.h
#pragma once

#include "State.h"

class Entity;
class Sprite;

class WinState : public State
{
public:
	WinState(System& system);
	~WinState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:
	System m_systems;
	Sprite* sprite;

};
