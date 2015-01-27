// Paddle.h

#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "Entity.h"

class Keyboard;

class Paddle : public Entity
{
public:
	Paddle(Keyboard* keyboard, Sprite* sprite, int width, int height);
	~Paddle();
	
	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();

	void Reset();

	bool IsVisible();
	void SetInvisible();
	EEntityType GetType();
	Collider* GetCollider();

private:
	Keyboard* m_keyboard;
	Sprite* m_sprite;
	Collider* m_collider;

	float m_x;
	float m_y;
	float m_speed;
	int m_screen_width;
	int m_screen_height;
	bool m_visible;
};

#endif // PADDLE_H_INCLUDED
