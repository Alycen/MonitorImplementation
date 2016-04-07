#ifndef _PLAYER_
#define _PLAYER_

#include "SFML\Graphics.hpp"
#include "InputManager.h"

class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f direction;
public:
	Player::Player()
	{
		position = sf::Vector2f(500, 500);

		texture.loadFromFile("player.png");
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}
	void Player::Update()
	{
		//X-Axis
		if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::A))
		{
			direction.x--;
		}
		else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::A))
		{
			direction.x++;
		}
		if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::D))
		{
			direction.x++;
		}
		else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::D))
		{
			direction.x--;
		}

		//Y-Axis
		if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::W))
		{
			direction.y--;
		}
		else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::W))
		{
			direction.y++;
		}
		if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::S))
		{
			direction.y++;
		}
		else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::S))
		{
			direction.y--;
		}

		float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		if (length > 0)
		{
			sf::Vector2f normalised = direction / length;
			position += normalised * 2.0f;
			sprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

			sprite.setPosition(position);
		}
	}

	void Player::Draw(sf::RenderWindow &win)
	{
		win.draw(sprite);
	}
};

#endif