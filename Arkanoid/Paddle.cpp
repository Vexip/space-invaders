// Paddle.cpp

#include "stdafx.h"

#include "Sprite.h"
#include "Collider.h"
#include "Paddle.h"
#include "Keyboard.h"

Paddle::Paddle(Keyboard* keyboard, Sprite* sprite, int screen_width, int screen_height)
{
	m_keyboard = keyboard;
	m_sprite = sprite;

	m_collider = new Collider(0, 0);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, 
		m_sprite->GetRegion()->h);

	m_x = 0.0f;
	m_y = 0.0f;
	m_screen_width = screen_width;
	m_screen_height = screen_height;

	m_speed = 200.0f;
	
	Reset();
}

Paddle::~Paddle()
{
	if (m_collider)
	delete m_collider;
}

void Paddle::Update(float deltatime)
{
	if (m_keyboard->IsKeyDown(97))
	{
		m_x -= m_speed * deltatime;
	}

	if (m_keyboard->IsKeyDown(100))
	{
		m_x += m_speed * deltatime;
	}
	if (m_x < 0.0f)
		
		m_x = 0.0f;
	//no more left then the window
	else if (m_x > m_screen_width - 32)
		m_x = m_screen_width - 32;

	m_collider->SetPosition(m_x, m_y);
}

Sprite* Paddle::GetSprite()
{
	return m_sprite;
}

Collider* Paddle::GetCollider()
{
	return m_collider;
}

float Paddle::GetX()
{
	return m_x;
}

float Paddle::GetY()
{
	return m_y;
}

void Paddle::Reset()
{
	m_x = m_screen_width / 2 - 40;
	m_y = m_screen_height - 60 - 8;
	m_collider->SetPosition(m_x, m_y);
}

bool Paddle::IsVisible() 
{
	return true;
}

void Paddle::SetInvisible()
{
	m_visible = false;
}

EEntityType Paddle::GetType()
{
	return ENTITY_PADDLE;
}
