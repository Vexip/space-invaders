// Ball.h

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Entity.h"
#include "SoundClip.h"


class Ball : public Entity
{
public:
	Ball(Sprite* sprite, int width, int height, float startX, float startY, SoundClip* shootSound);
	~Ball();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();

	void Reset(float x, float y);

	bool IsVisible();
	EEntityType GetType();
	Collider* GetCollider();

	void Activate();
	bool IsActive();
	void SetPosition(float x, float y);

	void InvertDirectionY();

	void checkOutOfBounds(float returnXPosition, float returnYPosition);

private:
	Sprite* m_sprite;
	Collider* m_collider;
	SoundClip* m_clip;

	int m_screen_width;
	int m_screen_height;

	float m_speed;
	float m_offset;
	float m_position_x;
	float m_position_y;
	float m_direction_y;

	float m_start_x;
	float m_start_y;
	
	bool m_active;
};

#endif // BALL_H_INCLUDED
