#include "SFML/Graphics.hpp"
#include "Bullets.h"

using namespace sf;
using namespace global;

Bullets::Bullets() {
	cnt = 0;
}

void Bullets::draw(sf::RenderWindow *window) {
	for (int i = 0; i < cnt; ++i) {
		sprite.setTextureRect(IntRect(0, list[i].type * frameY, frameX, frameY));
		sprite.setRotation(list[i].angle);
		sprite.setPosition(list[i].pos.x, list[i].pos.y);
		window->draw(sprite);
	}
}

void Bullets::add(int x, int y, double s, double ang, int t, int owner) {
	int dmg = (frameX + frameY) / 2;
	list.push_back(bullet(Vector2f(x, y), t, s, ang, std::min(frameX * scaleX, frameY * scaleY) / 2 / sqrt(2.), false, owner, dmg));
	cnt++;
}

void Bullets::checkKeyboard(float time) {

}

void Bullets::move(double time) {
	for (int i = 0; i < cnt; ++i) {
		list[i].pos = getNextPos(time, i);
		//std::cout << pos[i].x << " " << pos[i].y << "\n";
	}
}

Vector2f Bullets::getNextPos(double time, int i) {
	double dx = list[i].speed * sin(list[i].angle * PI / 180.) * time;
	double dy = -list[i].speed * cos(list[i].angle * PI / 180.) * time;
	double nextX = list[i].pos.x + dx;
	double nextY = list[i].pos.y + dy;

	return Vector2f(nextX, nextY);
}

void Bullets::updateAnimation(double time) {
	//sprite.setTextureRect(IntRect(curFrame * frameX, curType * frameY, frameX, frameY));
}

void Bullets::removeDead() {
	for (auto it = list.begin(); it != list.end();) {
		if ((*it).isDead) {
			it = list.erase(it);
			cnt--;
		} else
			it++;
	}
}

double Bullets::getFrameY() {
	return frameY;
}