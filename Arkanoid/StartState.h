//StartState.h
#pragma once

#include "State.h"

class Entity;
class Sprite;

class StartState : public State
{
public:
	StartState(System& system);
	~StartState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:
	System m_systems;
	Sprite* sprite;

};