#include "SFML/Graphics.hpp"
#include "Enemys.h"
#include "Booms.h"

using namespace sf;
using namespace global;

Enemys::Enemys() {
	cnt = 0;
}

void Enemys::draw(sf::RenderWindow *window) {
	for (int i = 0; i < cnt; ++i) {
		sprite.setTextureRect(IntRect(list[i].curFrame * frameX, list[i].type * frameY, frameX, frameY));
		sprite.setPosition(list[i].pos.x, list[i].pos.y);
		window->draw(sprite);
	}
}

void Enemys::add(int x, int y, int t) {
	int h = (frameX * scaleX + frameY * scaleY) / 2 * ENEMY_HP_FACTOR;

	list.push_back(enemy(sf::Vector2f(x, y), t, 0., 0., false, std::min(frameX * scaleX, frameY * scaleY) / 2 * 0.9, global::ENEMY_RATE_OF_FIRE, h));
	cnt++;
}

void Enemys::move(double time) {}


void Enemys::check(Booms *booms) {
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

void Enemys::updateAnimation(double time) {
	for (int i = 0; i < cnt; i++) {
		list[i].dTime += time;
		if (list[i].dTime > timeOnFrame) {
			list[i].dTime = 0;
			list[i].curFrame = (list[i].curFrame + 1) % numbFrame;
		}
	}
}

void Enemys::removeDead() {
	for (auto it = list.begin(); it != list.end();) {
		if (it->isDead) {
			it = list.erase(it);
			cnt--;
		} else
			it++;
	}
}

void Enemys::update(double time) {
	for (int i = 0; i < cnt; i++) {
		list[i].timeSinceLastShot += time;
	}
}

double getAngle(Vector2f v1, Vector2f v2) {
	double dot = (v1.x * v2.x + v1.y * v2.y);
	double cross = (v1.x * v2.y - v1.y * v2.x);
	return atan2(cross, dot) * 180. / PI;
}

void Enemys::shoot(Bullets *bullets, SpaceShip *ship) {
	for (int i = 0; i < cnt; i++) {
		Vector2f delta = ((Vector2f)list[i].pos - Vector2f(ship->getX(), ship->getY()));
		double len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
			
		if (list[i].timeSinceLastShot > list[i].rateOfFire && len < ENEMY_SHOOT_RAD) {
			Vector2f v1 = list[i].pos - Vector2f(ship->getX(), ship->getY());
			Vector2f v2 = Vector2f(0, -1);

			bullets->add(list[i].pos.x, list[i].pos.y, global::ENEMY_BULLET_SPEED, 180 - getAngle(v1, v2), 1, i);
			list[i].timeSinceLastShot = 0.;
		}
	}
}