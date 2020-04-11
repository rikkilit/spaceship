#include "SFML/Graphics.hpp"
#include "Asteroids.h"

using namespace sf;
using namespace global;

Asteroids::Asteroids() {
	cnt = 0;
}

void Asteroids::draw(sf::RenderWindow *window) {
	for (int i = 0; i < cnt; ++i) {
		sprite.setTextureRect(IntRect(0, list[i].type, frameX, frameY));
		sprite.setRotation(list[i].angle);
		sprite.setPosition(list[i].pos.x, list[i].pos.y);
		sprite.setScale(list[i].scal * scaleX, list[i].scal * scaleY);
		window->draw(sprite);
	}
}

void Asteroids::add(int x, int y) {
	double t = rand() % (numbFrame);
	double rs = (global::SHIP_ROTATION_SPEED / (1 + rand() % 100) * (1 - (2 * (rand() % 2))));
	double scal = (10 + rand() % 91) / 100.;
	double rad = (std::min(frameX * scaleX, frameY * scaleY) / 2 * scal / sqrt(2.));
	
	int h = (frameX * scaleX + frameY * scaleY) / 2 * ASTEROID_HP_FACTOR * scal;

	list.push_back(asteroid(Vector2f(x, y), t, rs, 0., rad, false, scal, h));
	
	cnt++;
}

void Asteroids::move(double time) {
	for (int i = 0; i < cnt; ++i) {
		if (list[i].isDead) {
			list[i].timeLeft -= time;
		}
		list[i].angle += list[i].rotateSpeed * time;
	}
}

void Asteroids::updateAnimation(double time) {

}

void Asteroids::removeDead() {
	for (auto it = list.begin(); it != list.end();) {
		if (it->isDead && it->timeLeft < 0.) {
			it = list.erase(it);
			cnt--;
		} else {
			it++;
		}
	}
}

void Asteroids::check(Booms *booms) {
	for (auto it = list.begin(); it != list.end(); it++) {
		if (it->hp <= 0 ) {
			if (!it->isDead)
				it->timeLeft = booms->getAnimationTime();
			it->isDead = true;
			if (!it->diedNow) {
				booms->add(it->pos.x, it->pos.y, 0, (it->rad * 3.5) / std::max(1., booms->getSize() ), 1);
				it->diedNow = true;
			}
		}
	}
}
