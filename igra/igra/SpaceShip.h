//SpaceShip.h
#ifndef __SPACESHIP_H__ 
#define __SPACESHIP_H__ 

#include "SFML/Graphics.hpp"

#include "Object.h"
#include "Bullets.h"

class SpaceShip : public Object {
protected:
	int hp, score;
	double speed;
	double curAc; // текущее ускорение
	double rateOfFire;


	int curFrame; // текущий кадр анимации
	int curType; // текущий тип объекта анимации

public:
	SpaceShip();
	
	double rad;
	bool isDead, diedNow; // флаги -- умер вообще и только что умер
	double timeLeft;

	double timeSinceLastShot; // время прошедшее с последнего выстрела

	void checkKeyboard(float); // проверка нажатия клавиш
	void move(double time); // перемещение объекта
	void draw(sf::RenderWindow *window); // отрисовка
	void scaleSpeed(double d); // изменение скорости
	void update(double time);
	void shoot(Bullets *bullets);

	void updateAnimation(double time);
	void takeDamage(int damage);
	void addScore(int d);

	sf::Vector2f getNextPos(double time); // следующая позиция
	
	// установка параметров класса
	void setAc(double ac);
	void setPos(double x, double y);
	void setRad();

	// запрос значений параметров класса
	double getAngle();
	int getHp();
	int getScore();
	double getSpeed();

};

#endif