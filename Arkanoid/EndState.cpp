//EndState.cpp
#include "stdafx.h"
#include "EndState.h"
#include "InputManager.h"
#include "State.h"
#include "Keyboard.h"
#include "GameState.h"
#include "StartState.h"
#include "sprite.h"
#include "SpriteManager.h"
#include "State.h"
#include "DrawManager.h"

EndState::EndState(System& system)
{
	m_systems = system;
}

EndState::~EndState()
{

}

bool EndState::Update(float deltatime)
{
	Keyboard* keyboard = m_systems.input_manager->GetKeyboard();
	if (keyboard->IsKeyDown(SDLK_RETURN))
	{
		return false;
	}
	
	return true;
}

void EndState::Draw()
{
	std::string filename = "../assets/end_screen.png";
	//Tagen från http://www.fansshare.com/gallery/photos/14547250/gameover-wallpaper/?loadimage

	Sprite* sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 0, 1280, 740);
	m_systems.draw_manager->Draw(sprite, 0, 0);
}

State* EndState::NextState()
{
	return new StartState(m_systems);
}