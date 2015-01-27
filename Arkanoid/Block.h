// Block.h

#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "Entity.h"

class Block : public Entity
{
public:
	Block(Sprite* sprite, float x, float y);
	~Block();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	void SetX(float m_x);
	float GetY();
	void SetY(float m_y);

	void Reset();

	void SetInvisible();
	bool IsVisible();

	void InvertDirectionX();

	EEntityType GetType();
	Collider* GetCollider();

private:
	Sprite* m_sprite;
	Collider* m_collider;
	float m_x;
	float m_y;
	bool m_visible;

	float m_speed;
	float m_offset;
	float m_position_x;
	float m_position_y;
	float m_direction_y;
	float m_direction_x;

	float m_start_x;
	float m_start_y;

};

#endif // BLOCK_H_INCLUDED
