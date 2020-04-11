//Object.h
#ifndef __OBJECT_H__ 
#define __OBJECT_H__ 

#include "SFML/Graphics.hpp"
#include "global.h"

class Object {
protected:
	int x, y; // положение объекта

	sf::Image image; // объект Image (изображение)
	sf::Texture texture;// объект Texture (текстура)
	sf::Sprite sprite; // объект Sprite(спрайт)

	int frameX, frameY; // ширина и высота одного кадра
	int numbFrame; // количество кадров в анимации
	int numbType; // количество типов отрисовки объекта
	double timeOnFrame; // время показа одного кадра анимации

public:
	
	double scaleX, scaleY; // масштабирование объекта по осям

	Object();

	virtual void draw(sf::RenderWindow *window) = 0; // отрисовка объекта
	virtual void move(double time) = 0; // движение объекта
	virtual void updateAnimation(double dTime) = 0; // обновление объекта

	void loadSprite(const std::string &filePath, int w, int h, double at); // загрузка спрайта
	
	void setScale(double sX, double sY); // изменение размеров объекта
	void setScale(double k); // изменение размеров объекта
	
	double getX();
	double getY();
	double getSize();
};

#endif