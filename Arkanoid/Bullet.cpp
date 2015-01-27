//Bullet.cpp
#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Bullet.h"
#include "SoundClip.h"

Bullet::Bullet(Sprite* sprite, int width, int height, float startX, float startY)
{
	m_screen_width = width;
	m_screen_height = height;

	m_sprite = sprite;

	m_speed = 400.0f;
	m_offset = -1.0f;
	m_position_x = m_start_x = startX + m_offset;
	m_position_y = m_start_y = startY + m_offset;

	m_collider = new Collider(startX, startY);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w - m_offset,
		m_sprite->GetRegion()->h - m_offset);

	
	m_active = false;
}
Bullet::~Bullet()
{
	if (m_collider)
		delete m_collider;
}
void Bullet::Update(float deltatime)
{
	if (!m_active)
		return;
	m_position_y -= m_direction_y * m_speed * deltatime;

	if (m_position_y > m_screen_height || m_position_y < 0.0f)
	{
		Reset();
		m_direction_y = -m_direction_y;
	}

	m_collider->SetPosition(m_position_x, m_position_y);
}
Sprite* Bullet::GetSprite()
{
	return m_sprite;
}
float Bullet::GetX()
{
	return m_position_x;
}
float Bullet::GetY()
{
	return m_position_y;
}
void Bullet::Reset()
{
	m_position_x = m_start_x;
	m_position_y = m_start_y;
	m_active = false;

	//m_collider->SetPosition(m_position_x, m_position_y);
}
bool Bullet::IsVisible()
{
	return true;
}
EEntityType Bullet::GetType()
{
	return ENTITY_BULLET;
}
void Bullet::SetPosition(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
	m_collider->Refresh();
}
Collider* Bullet::GetCollider()
{
	return m_collider;
}
void Bullet::Activate()
{
	m_active = true;
	m_direction_y = -1.0f;
}

bool Bullet::IsActive()
{
	return m_active;
}