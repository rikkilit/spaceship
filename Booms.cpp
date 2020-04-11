#include "SFML/Graphics.hpp"
#include "Booms.h"
#include "Asteroids.h"

using namespace sf;
using namespace global;

Booms::Booms() {
	cnt = 0;
}

void Booms::draw(sf::RenderWindow *window) {
	for (int i = 0; i < cnt; ++i) {
		if (!list[i].isDead) {
			sprite.setTextureRect(IntRect(list[i].curFrame * frameX, list[i].type * frameY, frameX, frameY));
			sprite.setPosition(list[i].pos.x, list[i].pos.y);
			sprite.setScale(list[i].scale, list[i].scale);
			window->draw(sprite);
			//sprite.setScale(scaleX * global::SCALE, scaleY * global::SCALE);
		}
	}
}

void Booms::add(int x, int y, int t, double scale, int nt) {
	list.push_back(boom(sf::Vector2f(x, y), (2 * t + (rand() % (nt))), 0., 0., false, scale));
	cnt++;
}

void Booms::move(double time) {}

void Booms::check() {
	for (int i = 0; i < cnt; i++) {
		if (list[i].curFrame >= numbFrame) {
			list[i].isDead = true;
		}
	}
}

void Booms::updateAnimation(double time) {
	for (int i = 0; i < cnt; i++) {
		list[i].dTime += time;
		if (list[i].dTime > timeOnFrame) {
			list[i].dTime = 0;
			list[i].curFrame = (list[i].curFrame + 1);
		}
	}
}

void Booms::removeDead() {
	for (auto it = list.begin(); it != list.end();) {
		if ((*it).isDead) {
			it = list.erase(it);
			cnt--;
		} else
			it++;
	}
}

double Booms::getAnimationTime() {
	return timeOnFrame * numbFrame;
}