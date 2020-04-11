//Background.h
#ifndef __BACKGROUND_H__ 
#define __BACKGROUND_H__ 

#include "SFML/Graphics.hpp"
#include "global.h"
#include "SpaceShip.h"

class Background {
protected:
	int x, y; // ��������� �������

	sf::Image image; // ������ Image (�����������)
	sf::Texture texture;// ������ Texture (��������)
	sf::Sprite sprite; // ������ Sprite(������)

	int frameX, frameY; // ������ � ������ ������ �����

	double scaleX, scaleY;

public:
	
	Background();

	void draw(sf::RenderWindow *window); // ��������� �������

	void loadSprite(const std::string &filePath); // �������� �������
	void setScale(double sX, double sY); // ��������� �������� �������
	void setScale(double k); // ��������� �������� �������
	void update(SpaceShip *ship);
};

#endif