//Asteroids.h
#ifndef __ASTEROID_H__ 
#define __ASTEROID_H__ 

#include "SFML/Graphics.hpp"
#include "Object.h"
#include "Booms.h"

// структура описывающая астероид
struct asteroid {
	// тип и здоровье астероида
	int type, hp;
	// текущий угол поворота, скорость поворота, радиус, масштаб, время прошедшее с момента смерти
	double angle, rotateSpeed, rad, scal, timeLeft;
	// флаги того, что он умер вообще и умер вот сейчас
	bool isDead, diedNow;
	// позиция
	sf::Vector2f pos;

	// конструктор структуры
	asteroid(sf::Vector2f p, int t, double rs, double a, double r, bool f, double s, int h) : 
		pos(p), type(t), rotateSpeed(rs), angle(a), rad(r), isDead(f), scal(s), hp(h), diedNow(false), timeLeft(0.) {};
};


class Asteroids : public Object {
protected:

public:
	// конструктор класса
	Asteroids();

	// список астероидов
	std::vector < asteroid > list;

	// их колличество
	int cnt;

	void draw(sf::RenderWindow *window); // отрисовка
	void add(int x, int y); // добавление нового
	void move(double time); // движение
	
	void updateAnimation(double time); // обновление анимации
	void removeDead(); // удаление уже умерших 
	void check(Booms * booms); // проверка на смерть
};

#endif