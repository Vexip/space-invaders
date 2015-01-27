//EndState.h
#pragma once

#include "State.h"

class Entity;
class Sprite;

class EndState : public State
{
public:
	EndState(System& system);
	~EndState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:
	System m_systems;
	Sprite* sprite;

};