// Ball.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Ball.h"
#include "SoundClip.h"


Ball::Ball(Sprite* sprite, int width, int height, float startX, float startY, SoundClip* shootSound)
{
	m_screen_width = width;
	m_screen_height = height;

	m_sprite = sprite;

	m_speed = 1000.0f;
	m_offset = 1.0f;
	m_position_x = m_start_x = startX + m_offset;
	m_position_y = m_start_y = startY + m_offset;

	m_collider = new Collider(startX, startY);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w - m_offset,
		m_sprite->GetRegion()->h - m_offset);

	m_clip = shootSound;
	m_active = false;
}

Ball::~Ball()
{
	if (m_collider)
		delete m_collider;
}

void Ball::Update(float deltatime)
{
	if (!m_active)
		return;

	m_position_y += m_direction_y * m_speed * deltatime;

	/*if (m_position_y > m_screen_height || m_position_y < 0.0f)
	{
		Reset();
		m_direction_y = -m_direction_y;
	}*/
	
	m_collider->SetPosition(m_position_x, m_position_y);
}

Sprite* Ball::GetSprite()
{
	return m_sprite;
}
float Ball::GetX()
{
	return m_position_x;
}

float Ball::GetY()
{
	return m_position_y;
}

void Ball::Reset(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
	m_active = false;

	m_collider->SetPosition(m_position_x, m_position_y);
}

bool Ball::IsVisible()
{
	return true;
}

EEntityType Ball::GetType()
{
	return ENTITY_BALL;
}

void Ball::SetPosition(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
	m_collider->Refresh();
}

void Ball::checkOutOfBounds(float returnXPosition, float returnYPosition)
{
	if (m_position_y > m_screen_height || m_position_y < 0.0f)
	{
		Reset(returnXPosition, returnYPosition);
		m_direction_y = -m_direction_y;
	}
}

Collider* Ball::GetCollider()
{
	return m_collider;
}

void Ball::Activate()
{
	if (m_active)
		return;

	// activate the ball
	m_active = true;

	// Shoot the ball

	m_direction_y = -1.0f;

	
	m_clip->Play();


}

bool Ball::IsActive()
{
	return m_active;
}