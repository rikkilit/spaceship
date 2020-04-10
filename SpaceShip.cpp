#include "SFML/Graphics.hpp"
#include "SpaceShip.h"

using namespace sf;
using namespace global;

SpaceShip::SpaceShip() {
	//speedX = 0., speedY = 0.;
	speed = 0.;
	score = 0;
	curFrame = 0;
	curType = 0;
	timeSinceLastShot = 0.;
	rateOfFire = global::SHIP_RATE_OF_FIRE;
	hp = global::SHIP_HP;
	isDead = false;
	diedNow = false;
	timeLeft = 0.;
}

void SpaceShip::setPos(double x, double y) {
	sprite.setPosition(x, y);
}

void SpaceShip::checkKeyboard(float time) {
	//curAc = 0;
	curAc = -global::SHIP_DECELERATION;
	bool brakes = true;

	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
		sprite.rotate(-SHIP_ROTATION_SPEED * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) { 	
		sprite.rotate(SHIP_ROTATION_SPEED * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		sprite.rotate(-SHIP_ROTATION_SPEED * time / 3);
	}
	if ( Keyboard::isKeyPressed(Keyboard::E)) { 	
		sprite.rotate(SHIP_ROTATION_SPEED * time / 3);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
		curAc = global::SHIP_ACCELERATION;
		brakes = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) { 
		curAc = -global::SHIP_ACCELERATION;
		brakes = false;
	}

	if (brakes) {
		if (speed > 0)
			speed = std::max(speed + curAc * time, 0.);
		else
			speed = std::min(speed - curAc * time, 0.);
	} else {
		speed += curAc * time;
	}
	//speed = std::max(speed + curAc, 0.);
}

void SpaceShip::move(double time) {
	/*
	double angle = sprite.getRotation();
	if (curAc == 0) {
		if (-global::SHIP_DECELERATION < speedX && speedX < global::SHIP_DECELERATION)
			speedX = 0;
		else if (speedX > 0.)
			speedX -= global::SHIP_DECELERATION * time;
		else 
			speedX += global::SHIP_DECELERATION * time;

		if (-global::SHIP_DECELERATION < speedY && speedY < global::SHIP_DECELERATION)
			speedY = 0;
		else if (speedY > 0.)
			speedY -= global::SHIP_DECELERATION * time;
		else 
			speedY += global::SHIP_DECELERATION * time;
	}
	else {
		std::cout << "second\n";
		speedX += curAc * sin(angle * PI / 180.) * time;
		speedY += -curAc * cos(angle * PI / 180.) * time;
	}

	//std::cout << speedX << " " << speedY << "\n";
	double dx = speedX * time + curAc * sin(angle * PI / 180.) * time * time / 2;
	double dy = speedY * time + -curAc * cos(angle * PI / 180.) * time * time / 2;
	sprite.move(dx, dy);
	*/

	sf::Vector2f nextPos = getNextPos(time);

	sprite.setPosition(nextPos.x, nextPos.y);
}


void SpaceShip::draw(sf::RenderWindow *window) {
	window->draw(sprite); //выводим спрайт на экран
}

void SpaceShip::setRad() {
	rad = std::min(frameX * scaleX, frameY * scaleY) / 2 * 0.9;
}

void SpaceShip::scaleSpeed(double d) {
	//speedX *= d, speedY *= d;
	speed *= d;
}

Vector2f SpaceShip::getNextPos(double time) {
	double angle = sprite.getRotation();
	double dx = speed * sin(angle * PI / 180.) * time;
	double dy = -speed * cos(angle * PI / 180.) * time;
	double nextX = sprite.getPosition().x + dx;
	double nextY = sprite.getPosition().y + dy;

	return Vector2f(nextX, nextY);
}

void SpaceShip::setAc(double a) {
	curAc = a;
}

double SpaceShip::getSpeed() {
	return speed;
}

double SpaceShip::getAngle() {
	return sprite.getRotation();
}

void SpaceShip::update(double time) {
	timeSinceLastShot += time;
	timeLeft -= time;
}

void SpaceShip::shoot(Bullets *bullets) {
	double angle = sprite.getRotation();
	if (timeSinceLastShot > rateOfFire && Keyboard::isKeyPressed(Keyboard::Space)) {
		bullets->add(getX() + bullets->getFrameY() / 2 * sin(angle * PI / 180.), 
					 getY() + bullets->getFrameY() / 2 * -cos(angle * PI / 180.), global::SHIP_BULLET_SPEED + speed, getAngle(), 0, -1);
		timeSinceLastShot = 0.;
	}
}

void SpaceShip::updateAnimation(double time) {
	sprite.setTextureRect(IntRect(curFrame * frameX, curType * frameY, frameX, frameY));
}

void SpaceShip::takeDamage(int damage) {
	hp = std::max(hp - damage, 0);
}

int SpaceShip::getHp() {
	return hp;
}

int SpaceShip::getScore() {
	return score;
}

void SpaceShip::addScore(int d) {
	score += d;
}