//Menu.h
#ifndef __MENU_H__ 
#define __MENU_H__ 

#include "SFML/Graphics.hpp"
#include "global.h"

#include "SpaceShip.h"

class Menu {
protected:
	sf::Font font;

	double x, y;

	int hp, score;
public:
	Menu();
	void update(SpaceShip *ship);
	void draw(sf::RenderWindow *window);
	void loadFont(const std::string &filePath);
};

#endif