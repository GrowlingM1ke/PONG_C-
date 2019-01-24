#include "ship.h"
#include "game.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[2] = {
	Keyboard::Right,  // Player2 UP
	Keyboard::Left // Player2 Down
};

Ship::Ship()
{
}

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

bool Invader::direction;
float Invader::speed;

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
		}
	}
}

//ship.cpp
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	//Move left and right
	if (Keyboard::isKeyPressed(controls[0])) {
		move(10.0f * dt, 0.0f);
	if (Keyboard::isKeyPressed(controls[1]))
		move(-10.0f * dt, 0.0f);
	}
}