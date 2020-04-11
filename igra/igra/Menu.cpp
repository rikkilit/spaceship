#include "Menu.h"

Menu::Menu() {}

void Menu::loadFont(const std::string &filePath) {
	font.loadFromFile(filePath); // Загрузка шрифта
}

void Menu::update(SpaceShip *ship) {
	x = ship->getX();
	y = ship->getY();

	hp = ship->getHp();
	score = ship->getScore();
}

void Menu::draw(sf::RenderWindow *window) {
	sf::Text text("", font, 40);
	text.setColor(sf::Color::Color(255, 255, 200, 200));

	std::ostringstream mySteam1;
	std::ostringstream mySteam2;
	mySteam1 << hp;
	mySteam2 << score;

	double newX = x - global::SCREEN_WIDTH / 2;
	double newY = y - global::SCREEN_HEIGHT / 2;
	text.setPosition(newX, newY);
	
	text.setString(" HP: " + mySteam1.str());
	window->draw(text);

	text.setString("\n Score: " + mySteam2.str());
	window->draw(text);
}