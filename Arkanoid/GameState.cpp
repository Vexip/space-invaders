// GameState.cpp

#include "stdafx.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "Bullet.h"

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include "GameState.h"

#include "SoundManager.h"
#include "SoundClip.h"

#include "Paddle.h"
#include "Block.h"
#include "Ball.h"
#include "Shield.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "EndState.h"


#include "SpriteText.h"
#include <SDL_ttf.h>

GameState::GameState(System& system)
{

	m_systems = system;

	std::string filename = "../assets/spaceinvaders.png";

	Sprite* sprite = m_systems.sprite_manager->CreateSprite(
		filename, 95, 0, 32, 16);

	Paddle* paddle = new Paddle(
		m_systems.input_manager->GetKeyboard(),
		sprite,
		m_systems.width,
		m_systems.height);
	m_entities.push_back(paddle);

	sprite = m_systems.sprite_manager->CreateSprite(
		filename, 134, 0, 6, 6);
	SoundClip* clip = m_systems.sound_manager->CreateSoundClip("../assets/Fire 1.wav");
	Ball* ball = new Ball(sprite,
		m_systems.width,
		m_systems.height,
        paddle->GetX() + 13, 
		paddle->GetY() - 6,
		clip);
	m_entities.push_back(ball);


	m_lives = 3;
	m_score = 0;
	life_3 = m_systems.sprite_manager->CreateSprite(filename, 95, 0, 32, 16);
	life_2 = m_systems.sprite_manager->CreateSprite(filename, 95, 0, 32, 16);
	life_1 = m_systems.sprite_manager->CreateSprite(filename, 95, 0, 32, 16);
	Bullet* bullet = new Bullet(sprite,
		m_systems.width,
		m_systems.height,
		m_systems.width / 2 - 8,
		m_systems.height - 68 - 16);
	m_entities.push_back(bullet);
	

	font = TTF_OpenFont("../assets/cs_regular.ttf", 20);
	if (!font)
	{
		printf("NEI");
	}

	m_scoreText = new SpriteText(m_systems.draw_manager->GetRenderer(), font, "Score: "  + std::to_string(m_score), 250, 250, 250);

	m_scoreSprite = new Sprite(m_scoreText->GetTexture());
	m_scoreSprite->setRegion(*m_scoreText->GetRegion());

	// hard coded block coordinates
	SDL_Rect enemies[] =
	{
		{ 0, 0, 22, 16 }, // middle
		{ 38, 0, 24, 16 }, // top
		{ 73, 0, 16, 16 }, // bottom
		{ 152, 0, 32, 14 }
	};

	// create all enemies for level
	int padding = 1;
	int xNumBlocks = (m_systems.width / 2) / (40 + padding);
	//int yNumBlocks = 7;
	int xOffset = (m_systems.width % (40 + padding)) / 2;
	int yOffset = xOffset;

	for (int y = 5; y < 7; y++)
	{
		for (int x = 0; x < xNumBlocks; x++)
		{
			SDL_Rect& rect = enemies[1];
			sprite = m_systems.sprite_manager->CreateSprite(
				filename, rect.x, rect.y, rect.w, rect.h);
			Block* block = new Block(sprite,
				(padding / 2) + xOffset + x * 40 + x * padding,
				yOffset + y * 16 + y * padding);
			m_entities.push_back(block);
			m_enemies.push_back(block);
		}

	}

	for (int y = 3; y < 5; y++)
	{
		for (int x = 0; x < xNumBlocks; x++)
		{
			SDL_Rect& rect = enemies[0];
			sprite = m_systems.sprite_manager->CreateSprite(
				filename, rect.x, rect.y, rect.w, rect.h);
			Block* block = new Block(sprite,
				padding + xOffset + x * 40 + x * padding,
				yOffset + y * 16 + y * padding);
			m_entities.push_back(block);
			m_enemies.push_back(block);
		}

	}

	for (int y = 1; y < 3; y++)
	{
		for (int x = 0; x < xNumBlocks; x++)
		{
			SDL_Rect& rect = enemies[2];
			sprite = m_systems.sprite_manager->CreateSprite(
				filename, rect.x, rect.y, rect.w, rect.h);
			Block* block = new Block(sprite,
				(padding * 4) + xOffset + x * 40 + x * (padding),
				yOffset + y * 16 + y * padding);
			m_entities.push_back(block);
			m_enemies.push_back(block);
		}

	}

	int xNumShields = (m_systems.width);
	int oxOffset = (m_systems.width % 5) / 2;
	int oyOffset = oxOffset;


	for (int y = 119; y < 120; y++)
	{
		for (int x = 44; x < 52; x++)
		{	
			sprite = m_systems.sprite_manager->CreateSprite(filename, 46, 0, 5, 5);
			Shield* shield = new Shield(sprite, oxOffset + x * 5, oyOffset + y * 5);
			m_entities.push_back(shield);
		}

		for (int x = 100; x < 108; x++)
		{
			sprite = m_systems.sprite_manager->CreateSprite(filename, 46, 0, 5, 5);
			Shield* shield = new Shield(sprite, oxOffset + x * 5, oyOffset + y * 5);
			m_entities.push_back(shield);
		}

		for (int x = 148; x < 156; x++)
		{
			sprite = m_systems.sprite_manager->CreateSprite(filename, 46, 0, 5, 5);
			Shield* shield = new Shield(sprite, oxOffset + x * 5, oyOffset + y * 5);
			m_entities.push_back(shield);
		}

		for (int x = 196; x < 204; x++)
		{
			sprite = m_systems.sprite_manager->CreateSprite(filename, 46, 0, 5, 5);
			Shield* shield = new Shield(sprite, oxOffset + x * 5, oyOffset + y * 5);
			m_entities.push_back(shield);
		}
	}
	
	m_active = false;
}

GameState::~GameState()
{
	int c = 0;
	auto it = m_entities.begin();
	while (it != m_entities.end())
	{
		Sprite* sprite = (*it)->GetSprite();
		if (sprite)
			m_systems.sprite_manager->DestroySprite(sprite);
		delete (*it);
		++it;
		c++;
	}
	m_entities.clear();
}

bool GameState::Update(float deltatime)
{
	UpdateScore();
	// update all entities
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		// update
		m_entities[i]->Update(deltatime);

		if (m_entities[i]->GetType() == ENTITY_BALL)
		{
			//   we check for entity type
			Ball* ball = static_cast<Ball*>(m_entities[i]);
			ball->checkOutOfBounds(m_entities[i]->GetX(), m_entities[i]->GetY());

			if (!ball->IsActive() && m_active)
			{
				// reset the game
				m_active = false;
			}
			else if (!ball->IsActive())
			{
				// here the ball follows the paddle
				Paddle* paddle = static_cast<Paddle*>(m_entities[0]);

				float paddleHalfWidth = paddle->GetSprite()->GetRegion()->w * 0.5f;
				float paddleHalfHeight = paddle->GetSprite()->GetRegion()->h * 0.5f;

				float paddlePosX = paddle->GetX();
				float paddlePosY = paddle->GetY();

				float ballHalfWidth = ball->GetSprite()->GetRegion()->w	* 0.5f;
				float ballHalfHeight = ball->GetSprite()->GetRegion()->h	* 0.5f;

				float ballNewX = paddlePosX + paddleHalfWidth - ballHalfWidth;
				float ballNewY = paddlePosY - paddleHalfHeight - ballHalfHeight;

				ball->SetPosition(ballNewX, ballNewY);

				Keyboard* keyboard = m_systems.input_manager->GetKeyboard();
				if (keyboard->IsKeyDown(32) && !m_active)
				{
					ball->Activate();
					m_active = true;
				}
			}
		}

		if (m_entities[i]->GetType() == ENTITY_BULLET)
		{

			Bullet* bullet = static_cast<Bullet*>(m_entities[i]);

			if (m_enemies.size() > 0)
			{
				if (!bullet->IsActive())
				{
					// Get random enemy
					//Hjälp av Anthon Fredriksson
					std::random_device rd;
					std::mt19937_64 generator(rd());
					std::uniform_int_distribution<int> distribution(0, m_enemies.size() -1);
					int random_enemy_index = distribution(generator);

					Block* block = static_cast<Block*>(m_enemies[random_enemy_index]);

					float blockHalfWidth = block->GetSprite()->GetRegion()->w * 0.5f;
					float blockHalfHeight = block->GetSprite()->GetRegion()->h * 0.5f;

					float blockPosX = block->GetX();
					float blockPosY = block->GetY();

					float bulletHalfWidth = bullet->GetSprite()->GetRegion()->w * 0.5f;
					float bulletHalfHeight = block->GetSprite()->GetRegion()->h	* 0.5f;

					float bulletNewX = blockPosX + blockHalfWidth - bulletHalfWidth;
					float bulletNewY = blockPosY - blockHalfHeight - bulletHalfHeight;


					bullet->SetPosition(bulletNewX, bulletNewY);
					bullet->Activate();
					m_active = true;
				}
			}
		}

	}
	bool edge = false;
	for (size_t i = 0; i < m_entities.size(); i++)//For loop, goes through all the enteties.
	{

		if (m_entities[i]->GetType() == ENTITY_BLOCK)//If an entity is a 'Block'
		{
			Block* block = static_cast<Block*>(m_entities[i]);

			if (block->GetX() >= m_systems.width - 24 || block->GetX() <= 0.0f)//if the enemies reaches the edges of the screen.
			{
				edge = true;//'edge' will be true.
				break;//Then brak the for loop ('edge' will be false again)
			}
		}
	}

	if (edge == true) //If 'edge' is true, it will...
	{
		for (size_t i = 0; i < m_entities.size(); i++)
		{

			if (m_entities[i]->GetType() == ENTITY_BLOCK)
			{
				Block* block = static_cast<Block*>(m_entities[i]);
				block->SetY(block->GetY() + 32);//Make it go down 32 pixels on screen.
				block->InvertDirectionX();//And change direction. 
			}
			
		}
	}
	for (size_t i = 0; i < m_entities.size(); i++)//For loop, goes through all the enteties.
	{

		if (m_entities[i]->GetType() == ENTITY_BLOCK)//If an entity is a 'Block'
		{
			Block* block = static_cast<Block*>(m_entities[i]);

			if (block->GetY() >= m_systems.height - 24 || block->GetY() <= 0.0f)//if the enemies reaches the edges of the screen.
			{
				m_lives--;
			}
			
		}
	}


	CollisionChecking();

	if (m_lives <= 0)
	{
		return false;
	}
	return true;

}
void GameState::Draw()
{

	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		Sprite* sprite = m_entities[i]->GetSprite();
		if (sprite)
		{
			m_systems.draw_manager->Draw(sprite,
				m_entities[i]->GetX(),
				m_entities[i]->GetY());
		}
	}
	if (m_lives == 3)
	{
		m_systems.draw_manager->Draw(life_3, 0, 10);
		m_systems.draw_manager->Draw(life_3, 50, 10);
		m_systems.draw_manager->Draw(life_3, 100, 10);
	}
	else if (m_lives == 2)
	{
		delete life_3;
		life_3 = nullptr;
		m_systems.draw_manager->Draw(life_2, 0, 10);
		m_systems.draw_manager->Draw(life_2, 50, 10);
	}
	else if (m_lives == 1)
	{
		delete life_2;
		life_2 = nullptr;
		m_systems.draw_manager->Draw(life_1, 0, 10);
	}

	m_systems.draw_manager->Draw(m_scoreSprite, 1000, 6);

}
void GameState::UpdateScore()
{
	m_scoreText->Set("Score: " + std::to_string(m_score));
	m_scoreSprite->setTexture(m_scoreText->GetTexture());
	m_scoreSprite->setRegion(*m_scoreText->GetRegion());

}

State* GameState::NextState()
{
		return new EndState(m_systems);
}


// private
void GameState::CollisionChecking()
{
	Paddle* paddle = static_cast<Paddle*>(m_entities[0]);
	Ball* ball = static_cast<Ball*>(m_entities[1]);
	Bullet* bullet = static_cast<Bullet*>(m_entities[2]);
	Block* block = static_cast<Block*>(m_entities[3]);
	Shield* shield = static_cast<Shield*>(m_entities[4]);

	int overlapX = 0, overlapY = 0;


	if (CollisionManager::Check(bullet->GetCollider(), paddle->GetCollider(), overlapX, overlapY))
	{

		if (overlapY != 0)
		{
			paddle->Reset();
			bullet->Reset();
			//bullet->SetPosition(bullet->GetX() + overlapX, bullet->GetY() + overlapY);
			//paddle->SetInvisible();
			--m_lives;
		}

		if (overlapX != 0)
		{
			paddle->Reset();
			bullet->Reset();
		}
	}
	if (CollisionManager::Check(bullet->GetCollider(), ball->GetCollider(), overlapX, overlapY))
	{
		if (overlapY != 0)
		{
			/*bullet->Reset();*/
			ball->Reset(paddle->GetX(), paddle->GetY());
		}
		if (overlapX != 0)
		{
			/*bullet->Reset();*/
			ball->Reset(paddle->GetX(), paddle->GetY());
		}
	}
	
		for (unsigned int i = 2; i < m_entities.size(); i++)
		{
			if (m_entities[i]->GetType() == ENTITY_SHIELD)
			{
				Shield* shield = static_cast<Shield*>(m_entities[i]);
				if (CollisionManager::Check(bullet->GetCollider(), shield->GetCollider(), overlapX, overlapY))
				{
					shield->SetInvisible();
					bullet->Reset();
				}
			}
		}
		
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i]->GetType() == ENTITY_BLOCK || m_entities[i]->GetType() == ENTITY_BULLET || m_entities[i]->GetType() == ENTITY_SHIELD)
			{
				Block* block = static_cast<Block*>(m_entities[i]);
				if (!block->IsVisible())
					continue;

				if (ball->IsActive() == true)
				{
					if (CollisionManager::Check(ball->GetCollider(), block->GetCollider(), overlapX, overlapY))
					{
						block->SetInvisible();

						//When "ball" collides with "block" it resets

						if (overlapY != 0)
							ball->Reset(paddle->GetX(), paddle->GetY());

						if (overlapX != 0)
							ball->Reset(paddle->GetX(), paddle->GetY());

						++m_score;
						
						ball->SetPosition(paddle->GetX(), paddle->GetY());
						
					}
				}
			}
		}
	}

