#include "Background.h"

using namespace sf;

Background::Background() {
	x = 0; y = 0;
	scaleX = 1., scaleY = 1.;
}

void Background::loadSprite(const std::string &filePath) {
	image.loadFromFile(filePath); //загружаем в него файл
	texture.loadFromImage(image); //передаем в него объект Image (изображения)

	frameX = image.getSize().x;
	frameY = image.getSize().y;

	sprite.setTexture(texture); //передаём в него объект Texture (текстуры)
	sprite.setOrigin(frameX / 2., frameY / 2.);
}

void Background::setScale(double sX, double sY) {
	scaleX *= sX, scaleY *= sY;
	sprite.setScale(scaleX, scaleY);
}

void Background::setScale(double k) {
	scaleX *= k, scaleY *= k;
	sprite.setScale(k, k);
}

void Background::draw(sf::RenderWindow *window) {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			sprite.setPosition(x + frameX * i, y + frameY * j);
			window->draw(sprite); //выводим спрайт на экран
		}
	}
}

void Background::update(SpaceShip *ship) {
	if (ship->getX() < x && x - ship->getX() > frameX)
		x -= frameX;
	if (ship->getX() > x && ship->getX() - x > frameX)
		x += frameX;
	if (ship->getY() < y && y - ship->getY() > frameY)
		y -= frameY;
	if (ship->getY() > y && ship->getY() - y > frameY)
		y += frameY;
}