//WinState.cpp
#include "stdafx.h"
#include "WinState.h"
#include "InputManager.h"
#include "State.h"
#include "Keyboard.h"
#include "GameState.h"
#include "StartState.h"
#include "sprite.h"
#include "SpriteManager.h"
#include "State.h"
#include "DrawManager.h"

WinState::WinState(System& system)
{
	m_systems = system;
}

WinState::~WinState()
{

}

bool WinState::Update(float deltatime)
{
	Keyboard* keyboard = m_systems.input_manager->GetKeyboard();
	if (keyboard->IsKeyDown(SDLK_RETURN))
	{
		return false;
	}

	return true;
}

void WinState::Draw()
{
	std::string filename = "../assets/WinState.png";
	//Tagen från http://www.fansshare.com/gallery/photos/14547250/gameover-wallpaper/?loadimage

	Sprite* sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 0, 1280, 740);
	m_systems.draw_manager->Draw(sprite, 0, 0);
}

State* WinState::NextState()
{
	return new StartState(m_systems);
}