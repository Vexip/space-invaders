////StartState.cpp
//
#include "stdafx.h"
#include "StartState.h"
#include "InputManager.h"
#include "State.h"
#include "Keyboard.h"
#include "GameState.h"
#include "sprite.h"
#include "SpriteManager.h"
#include "State.h"
#include "DrawManager.h"
StartState::StartState(System& system)
{
	m_systems = system;
}

StartState::~StartState()
{
	if (sprite)
		m_systems.sprite_manager->DestroySprite(sprite);
}

bool StartState::Update(float deltatime)
{
	Keyboard* keyboard = m_systems.input_manager->GetKeyboard();
	if (keyboard->IsKeyDown(SDLK_RETURN))
	{
		return false;
	}
	return true;
}

void StartState::Draw()
{

	std::string filename = "../assets/start_screen.png";
	//Tagen från http://www.1wallpaperhd.com/2014/10/space-invaders-wallpaper-05.html

	Sprite* sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 0, 1280, 740);
	m_systems.draw_manager->Draw(sprite, 0, 0);
}

State* StartState::NextState()
{
	return new GameState(m_systems);
}