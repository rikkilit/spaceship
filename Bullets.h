//Bullet.h
#ifndef __BULLET_H__ 
#define __BULLET_H__ 

#include "SFML/Graphics.hpp"
#include "Object.h"

struct bullet {
	int type, damage;
	double angle, speed, rad;
	bool isDead;
	sf::Vector2f pos;
	int owner;

	bullet(sf::Vector2f p, int t, double s, double a, double r, bool f, int o, int dmg) : 
		pos(p), type(t), speed(s), angle(a), rad(r), isDead(f), owner(o), damage(dmg) {};
};

class Bullets : public Object {
protected:

public:
	Bullets();

	std::vector < bullet > list;

	int cnt;

	void draw(sf::RenderWindow *window);
	void add(int x, int y, double s, double ang, int t, int);
	void checkKeyboard(float time);
	void move(double time);
	sf::Vector2f getNextPos(double time, int i);

	void updateAnimation(double time);

	void removeDead();

	double getFrameY();
};

#endif