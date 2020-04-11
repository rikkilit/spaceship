//Object.h
#ifndef __OBJECT_H__ 
#define __OBJECT_H__ 

#include "SFML/Graphics.hpp"
#include "global.h"

class Object {
protected:
	int x, y; // ��������� �������

	sf::Image image; // ������ Image (�����������)
	sf::Texture texture;// ������ Texture (��������)
	sf::Sprite sprite; // ������ Sprite(������)

	int frameX, frameY; // ������ � ������ ������ �����
	int numbFrame; // ���������� ������ � ��������
	int numbType; // ���������� ����� ��������� �������
	double timeOnFrame; // ����� ������ ������ ����� ��������

public:
	
	double scaleX, scaleY; // ��������������� ������� �� ����

	Object();

	virtual void draw(sf::RenderWindow *window) = 0; // ��������� �������
	virtual void move(double time) = 0; // �������� �������
	virtual void updateAnimation(double dTime) = 0; // ���������� �������

	void loadSprite(const std::string &filePath, int w, int h, double at); // �������� �������
	
	void setScale(double sX, double sY); // ��������� �������� �������
	void setScale(double k); // ��������� �������� �������
	
	double getX();
	double getY();
	double getSize();
};

#endif