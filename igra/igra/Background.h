//Background.h
#ifndef __BACKGROUND_H__ 
#define __BACKGROUND_H__ 

#include "SFML/Graphics.hpp"
#include "global.h"
#include "SpaceShip.h"

class Background {
protected:
	int x, y; // положение объекта

	sf::Image image; // объект Image (изображение)
	sf::Texture texture;// объект Texture (текстура)
	sf::Sprite sprite; // объект Sprite(спрайт)

	int frameX, frameY; // ширина и высота одного кадра

	double scaleX, scaleY;

public:
	
	Background();

	void draw(sf::RenderWindow *window); // отрисовка объекта

	void loadSprite(const std::string &filePath); // загрузка спрайта
	void setScale(double sX, double sY); // изменение размеров объекта
	void setScale(double k); // изменение размеров объекта
	void update(SpaceShip *ship);
};

#endif