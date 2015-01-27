// InputManager.cpp

#include "stdafx.h"

#include "Keyboard.h"
#include "InputManager.h"

InputManager::InputManager()
{
	
	m_keyboard = new Keyboard;
}

InputManager::~InputManager()
{
	
	if (m_keyboard)
	{
		delete m_keyboard;
		m_keyboard = nullptr;
	}
}


Keyboard* InputManager::GetKeyboard()
{
	return m_keyboard;
}

void InputManager::SetKeyboard(int key, bool state)
{
	m_keyboard->SetKeyboard(key, state);
}
