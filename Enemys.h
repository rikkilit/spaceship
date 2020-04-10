//Enemys.h
#ifndef __ENEMYS_H__ 
#define __ENEMYS_H__ 

#include "SFML/Graphics.hpp"
#include "Object.h"
#include "SpaceShip.h"
#include "Booms.h"

struct enemy {
	int type, curFrame, hp;
	double dTime, rad, scal, timeLeft;
	bool isDead, diedNow;
	sf::Vector2f pos;

	double rateOfFire;
	double timeSinceLastShot;

	enemy(sf::Vector2f p, int t, double dt, double cf, bool f, double r, double rf, int h) : 
		pos(p), type(t), dTime(dt), curFrame(cf), isDead(f), rad(r), timeSinceLastShot(0.), rateOfFire(rf), hp(h), timeLeft(0.), diedNow(false) {};
};

class Enemys : public Object {
protected:

public:
	Enemys();

	std::vector < enemy > list;

	int cnt;

	void draw(sf::RenderWindow *window);
	void add(int x, int y, int type);
	void move(double time);
	void updateAnimation(double time);
	void shoot(Bullets *bullets, SpaceShip *ship);

	void check(Booms *booms);
	void update(double time);

	void removeDead();
};

#endif