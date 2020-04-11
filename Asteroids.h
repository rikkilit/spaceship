//Asteroids.h
#ifndef __ASTEROID_H__ 
#define __ASTEROID_H__ 

#include "SFML/Graphics.hpp"
#include "Object.h"
#include "Booms.h"

// ��������� ����������� ��������
struct asteroid {
	// ��� � �������� ���������
	int type, hp;
	// ������� ���� ��������, �������� ��������, ������, �������, ����� ��������� � ������� ������
	double angle, rotateSpeed, rad, scal, timeLeft;
	// ����� ����, ��� �� ���� ������ � ���� ��� ������
	bool isDead, diedNow;
	// �������
	sf::Vector2f pos;

	// ����������� ���������
	asteroid(sf::Vector2f p, int t, double rs, double a, double r, bool f, double s, int h) : 
		pos(p), type(t), rotateSpeed(rs), angle(a), rad(r), isDead(f), scal(s), hp(h), diedNow(false), timeLeft(0.) {};
};


class Asteroids : public Object {
protected:

public:
	// ����������� ������
	Asteroids();

	// ������ ����������
	std::vector < asteroid > list;

	// �� �����������
	int cnt;

	void draw(sf::RenderWindow *window); // ���������
	void add(int x, int y); // ���������� ������
	void move(double time); // ��������
	
	void updateAnimation(double time); // ���������� ��������
	void removeDead(); // �������� ��� ������� 
	void check(Booms * booms); // �������� �� ������
};

#endif