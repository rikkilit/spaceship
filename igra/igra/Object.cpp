#include "Object.h"

using namespace sf;

Object::Object() {
	//dTime = 0;
	//x = global::SCREEN_WIDTH / 2;
	//y = global::SCREEN_HEIGHT / 2;
	x = 0; y = 0;
	scaleX = 1., scaleY = 1.;
}

void Object::loadSprite(const std::string &filePath, int w, int h, double animationTime) {
	numbFrame = w;
	numbType = h;
	timeOnFrame = animationTime / numbFrame;

	image.loadFromFile(filePath); //загружаем в него файл
	texture.loadFromImage(image); //передаем в него объект Image (изображения)

	frameX = image.getSize().x / w;
	frameY = image.getSize().y / h;

	sprite.setTexture(texture); //передаём в него объект Texture (текстуры)
	
	sprite.setOrigin(frameX / 2., frameY / 2.);
}

void Object::setScale(double sX, double sY) {
	scaleX *= sX, scaleY *= sY;
	sprite.setScale(scaleX, scaleY);
}

void Object::setScale(double k) {
	scaleX *= k, scaleY *= k;
	sprite.setScale(k, k);
}

double Object::getX() {
	return sprite.getPosition().x;
}

double Object::getY() {
	return sprite.getPosition().y;
}

double Object::getSize() {
	return std::max(frameX, frameY);
}