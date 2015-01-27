// Block.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Block.h"

Block::Block(Sprite* sprite, float x, float y)
{
	m_sprite = sprite;

	m_direction_x = 1.0f;

	m_speed = 100;
	/*m_offset = 1.0f;*/
	m_position_x = m_start_x = x + m_offset;
	m_position_y = m_start_y = y + m_offset;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, 
		m_sprite->GetRegion()->h);

	/*m_x = x;
	m_y = y;
*/
	m_visible = true;
}

Block::~Block()
{
	if (m_collider)
	delete m_collider;
}

void Block::Update(float deltatime)
{

	m_collider->SetPosition(m_position_x, m_position_y);

	m_position_x += m_direction_x * m_speed * deltatime;
}

Sprite* Block::GetSprite()
{
	return m_sprite;
}

float Block::GetX()
{
	return m_position_x;
}

float Block::GetY()
{
	return m_position_y;
}

void Block::SetY(float m_y)
{
	m_position_y = m_y;
}

void Block::SetX(float m_x)
{
	m_position_x = m_x;
}

void Block::Reset()
{
	m_visible = true;
}

void Block::SetInvisible()
{
	m_visible = false;
}

bool Block::IsVisible()
{
	return m_visible;
}

void Block::InvertDirectionX()
{
	m_direction_x = -m_direction_x;
}

EEntityType Block::GetType()
{
	return ENTITY_BLOCK;
}

Collider* Block::GetCollider()
{
	return m_collider;
}
