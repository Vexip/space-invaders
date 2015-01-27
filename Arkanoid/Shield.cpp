//Shield.cpp
#include "stdafx.h"
#include "Sprite.h"
#include "Shield.h"
#include "Collider.h"

Shield::Shield(Sprite* sprite, float x, float y)
{
	m_sprite = sprite;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;
	m_visible = true;
}

void Shield::Update(float deltatime)
{
}

Sprite* Shield::GetSprite()
{
	return m_sprite;
}

float Shield::GetX()
{
	return m_x;
}

float Shield::GetY()
{
	return m_y;
}

void Shield::Reset()
{

}

void Shield::SetInvisible()
{
	m_visible = false;
}

bool Shield::IsVisible()
{
	return m_visible;
}
EEntityType Shield::GetType()
{
	return ENTITY_SHIELD;
}

Collider* Shield::GetCollider()
{
	return m_collider;
}