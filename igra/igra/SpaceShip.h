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
	double curAc; // ������� ���������
	double rateOfFire;


	int curFrame; // ������� ���� ��������
	int curType; // ������� ��� ������� ��������

public:
	SpaceShip();
	
	double rad;
	bool isDead, diedNow; // ����� -- ���� ������ � ������ ��� ����
	double timeLeft;

	double timeSinceLastShot; // ����� ��������� � ���������� ��������

	void checkKeyboard(float); // �������� ������� ������
	void move(double time); // ����������� �������
	void draw(sf::RenderWindow *window); // ���������
	void scaleSpeed(double d); // ��������� ��������
	void update(double time);
	void shoot(Bullets *bullets);

	void updateAnimation(double time);
	void takeDamage(int damage);
	void addScore(int d);

	sf::Vector2f getNextPos(double time); // ��������� �������
	
	// ��������� ���������� ������
	void setAc(double ac);
	void setPos(double x, double y);
	void setRad();

	// ������ �������� ���������� ������
	double getAngle();
	int getHp();
	int getScore();
	double getSpeed();

};

#endif