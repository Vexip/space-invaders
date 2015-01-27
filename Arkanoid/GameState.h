// GameState.h

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "SDL_ttf.h"
#include "State.h"

class Entity;
class SpriteText;

class GameState : public State
{
	friend DrawManager;
public:
	GameState(System& system);
	~GameState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();
	void UpdateScoreTxt();
	void UpdateScore();

private:
	void CollisionChecking();

private:
	Sprite* m_scoreSprite;
	SpriteText* m_scoreText;
	System m_systems;
	TTF_Font *font;
	SDL_Texture* fontTexture;
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_enemies;
	Sprite *life_3;
	Sprite *life_2;
	Sprite *life_1;
	int m_lives;
	int m_score;
	bool m_active;
};

#endif // GAMESTATE_H_INCLUDED
