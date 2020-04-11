//Booms.h
#ifndef __BOOM_H__ 
#define __BOOM_H__ 

#include "SFML/Graphics.hpp"
#include "Object.h"

struct boom {
	int type, curFrame;
	double dTime, scale, timeLeft;
	bool isDead;
	sf::Vector2f pos;

	boom(sf::Vector2f p, int t, double dt, double cf, bool f, double sc) : 
		pos(p), type(t), dTime(dt), curFrame(cf), isDead(f), scale(sc) {};
};

class Booms : public Object {
protected:

public:
	Booms();

	std::vector < boom > list;

	int cnt;

	void draw(sf::RenderWindow *window);
	void add(int x, int y, int type, double scale, int);
	void move(double time);
	void updateAnimation(double time);

	void check();

	void removeDead();
	double getAnimationTime();
};

#endif