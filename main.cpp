//main.cpp
#include <SFML/Graphics.hpp>

#include "global.h"
#include "SpaceShip.h"
#include "Asteroids.h"
#include "Bullets.h"
#include "Booms.h"
#include "Enemys.h"
#include "Background.h"
#include "Menu.h"

using namespace sf;
using namespace std; 
using namespace global; 

sf::View myView;

// ������� ������������ ������ � ��������� ����������
void getPlayerCoordinateForView(double x, double y) {
	myView.setCenter(x, y);
}

// ��������� ��������� � ������
Asteroids asteroids;
Enemys enemys;

// ���������� ������� �� �����
void generateMap() {
	int NUMBER = 3000; // ������, � ������� ����� �������������� �������

	// ��������� ����������
	bool f = false;
	int k = 300 + rand() % 100, x, y;
	for (int i = 0; i < k; ++i) {
		do {
			// ���������� ��������� ����������
			x = -NUMBER + rand() % (2 * NUMBER);
			y = -NUMBER + rand() % (2 * NUMBER);

			// ��������� �� ��������� ����������� � �������
			f = false;
			for (int i = 0; i < asteroids.cnt; i++) {
				Vector2f delta = ((Vector2f)asteroids.list[i].pos - Vector2f(x, y));
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
				if (len < 2.2 * asteroids.list[i].rad) {
					f = true;
				}
			}
		// � ����� �������� ��������� -- ����� �� ������, �� � �� � ����� ������
		} while (x * x + y * y > NUMBER * NUMBER || x * x + y * y < 200 * 200 || f);
		asteroids.add(x, y); // ���������� ���������
	}

	// ��������� ������ (���������� ����������)
	k = 100 + rand() % 100, x, y;
	for (int i = 0; i < k; ++i) {
		do {
			x = -NUMBER + rand() % (2 * NUMBER);
			y = -NUMBER + rand() % (2 * NUMBER);

			f = false;
			for (int i = 0; i < asteroids.cnt; i++) {
				Vector2f delta = ((Vector2f)asteroids.list[i].pos - Vector2f(x, y));
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
				if (len < 2.2 * asteroids.list[i].rad) {
					f = true;
				}
			}
			for (int i = 0; i < enemys.cnt; i++) {
				Vector2f delta = ((Vector2f)enemys.list[i].pos - Vector2f(x, y));
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
				if (len < 2.2 * enemys.list[i].rad) {
					f = true;
				}
			}

		} while (x * x + y * y > NUMBER * NUMBER || x * x + y * y < 200 * 200 || f);
		enemys.add(x, y, 0);
	}
}

int main()
{
	//sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(global::SCREEN_WIDTH, global::SCREEN_HEIGHT/*, desktop.bitsPerPixel*/), "MyGame");
	myView.reset(sf::FloatRect(0, 0, global::SCREEN_WIDTH, global::SCREEN_HEIGHT));

	srand(time(NULL)); // ������ ������ ��� ������

	Clock clock;

	Menu menu;

	// ���������  ����� � ������� �� ������, ��� �������� ������ ������
	menu.loadFont("11870.otf");

	SpaceShip ship;
	ship.loadSprite("images/spaceship1.png", 1, 1, 1000.);
	ship.setScale(0.5 * global::SCALE);
	ship.setRad();

	asteroids.loadSprite("images/meteors.png", 1, 4, 1000.);
	asteroids.setScale(global::SCALE);

	Bullets bullets;
	bullets.loadSprite("images/lasersShot.png", 1, 2, 1000.);
	bullets.setScale(1. * global::SCALE, 1.0 * global::SCALE);

	Booms booms, booms2; // ������ ������� � ������ �����������
	booms.loadSprite("images/Bang.png", 2, 4, 200.);
	booms.setScale(0.7 * global::SCALE);
	booms2.loadSprite("images/bigbang.png", 9, 1, 1000.);
	booms2.setScale(1);

	enemys.loadSprite("images/ufoRedForever2.png", 2, 1, 1000.);
	enemys.setScale(global::SCALE);

	Background background;
	background.loadSprite("images/space3.png");

	ship.setPos(0., 0.);

	generateMap();

	while (window.isOpen())  //���� ���� �������
	{
		float time = clock.getElapsedTime().asMicroseconds(); // ���� ��������� ����� � �������������
		clock.restart(); // ������������� �����
		time = time/800; // �������� ����
		//std::cout << time << "\n"; // ������� ��� ����� ����� (���������������, ��� �����)
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

		sf::Event event;
		while (window.pollEvent(event)) // �������� ����
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		ship.update(time); // ��������� ��������� ������� (����� � ���������� ��������)
		enemys.update(time);
		ship.checkKeyboard(time); // ����������

		ship.shoot(&bullets); // ��������
		enemys.shoot(&bullets, &ship); // ��������

		// ��������� ������������ ������� � ����������
		for (int i = 0; i < asteroids.cnt; i++) {
			Vector2f delta = ((Vector2f)asteroids.list[i].pos - ship.getNextPos(time));
			double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // ��������� ����� ���������
			if (len < ship.rad + asteroids.list[i].rad) {
				if (asteroids.list[i].hp > 0) {
					asteroids.list[i].hp -= ship.getSpeed() * SPEED_DAMAGE_FACTOR; // ������� ���� �������������
					ship.scaleSpeed(-global::COLLISION_FACTOR); // �������� �������� �������
					ship.setAc(-global::SHIP_ACCELERATION); // �������� ��������� �������
				}
			}
		}

		// ��������� ������������ ���� � ����������
		for (int i = 0; i < bullets.cnt; i++) {
			Vector2f bulNextPos = bullets.getNextPos(time, i);
			for (int j = 0; j < asteroids.cnt; j++) {
				Vector2f delta = ((Vector2f)asteroids.list[j].pos - bulNextPos);
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // ��������� ����� ���������
				if (len < asteroids.list[j].rad) {
					bullets.list[i].isDead = true; // ������� ����
					booms.add(bulNextPos.x, bulNextPos.y, bullets.list[i].type, booms.scaleX, 2); // ������� �������� �����
					asteroids.list[j].hp -= bullets.list[i].damage; // ������� ���� �� ����

					if (asteroids.list[j].hp <= 0 && bullets.list[i].type == 0) { // ���� �������� ����� � ��� ���� ������
						ship.addScore(asteroids.list[j].rad * 5); // �������� ����
					}
				}
			}
		}

		// ��������� ������������ ���� � ������
		for (int i = 0; i < bullets.cnt; i++) {
			Vector2f bulNextPos = bullets.getNextPos(time, i);
			for (int j = 0; j < enemys.cnt; j++) {
				Vector2f delta = ((Vector2f)enemys.list[j].pos - bulNextPos);
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // ��������� ����� ���������
				if (len < enemys.list[j].rad && bullets.list[i].owner != j) { // �������������� ��������: ���� �� ������������ � ���, ��� �� ��������
					bullets.list[i].isDead = true; // ������� ����
					booms.add(bulNextPos.x, bulNextPos.y, bullets.list[i].type, booms.scaleX, 2); // ������� �������� �����
					enemys.list[j].hp -= bullets.list[i].damage; // ������� ���� �� ����
					
					if (enemys.list[j].hp <= 0 && bullets.list[i].type == 0) { // ���� ���� ����� � ��� ���� ������
						ship.addScore(enemys.list[j].rad * 10); // �������� ����
					}
				}
			}
		}

		// ��������� ������������ ������� � �����
		for (int i = 0; i < enemys.cnt; i++) {
			Vector2f delta = ((Vector2f)enemys.list[i].pos - ship.getNextPos(time));
			double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // ��������� ����� ���������
			if (len < ship.rad + enemys.list[i].rad) {
				if (enemys.list[i].hp > 0) {
					enemys.list[i].hp -= ship.getSpeed() * SPEED_DAMAGE_FACTOR; // ������� ���� �������������
					ship.scaleSpeed(-global::COLLISION_FACTOR); // �������� �������� �������
					ship.setAc(-global::SHIP_ACCELERATION); // �������� ��������� �������
				}
			}
		}

		// ��������� ������������ ������� � ����
		for (int i = 0; i < bullets.cnt; i++) {
			Vector2f bulNextPos = bullets.getNextPos(time, i);
			Vector2f delta = ((Vector2f)bullets.list[i].pos - ship.getNextPos(time));
			double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // ��������� ����� ���������
			if (len < ship.rad && bullets.list[i].owner != -1) { // �������������� ��������: ���� �� ������������ � ���, ��� �� ��������
				ship.takeDamage(bullets.list[i].damage); // ������� ���� �� ����
				bullets.list[i].isDead = true; // ������� ����
				booms.add(bulNextPos.x, bulNextPos.y, bullets.list[i].type, booms.scaleX, 2); // ������� �������� �����
			}
		}
		
		// ����������� 
		if (ship.getHp() > 0)
			ship.move(time);
		asteroids.move(time); 
		bullets.move(time);

		// ��������� ��������
		background.update(&ship);
		booms.updateAnimation(time);
		booms2.updateAnimation(time);
		enemys.updateAnimation(time);
		ship.updateAnimation(time);

		// ��������� �� ���������
		booms.check();
		booms2.check();
		enemys.check(&booms2);
		asteroids.check(&booms2);

		// ���������� ������ �� �������
		getPlayerCoordinateForView(ship.getX(), ship.getY());

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		window.setView(myView); // ������ ������
		window.clear(); // ������!
		
		menu.update(&ship);

		// ������������ �������
		background.draw(&window);
		asteroids.draw(&window);
		bullets.draw(&window);
		enemys.draw(&window);
		if (!ship.isDead || !ship.timeLeft < 0)
			ship.draw(&window);
		booms.draw(&window);
		booms2.draw(&window);
		menu.draw(&window);

		window.display(); //���������� ������������ �� ������

		// ������� ������� �������
		bullets.removeDead();
		booms.removeDead();
		booms2.removeDead();
		asteroids.removeDead();
		enemys.removeDead();

		// �������� ������� �� ����� ����
		if (ship.getHp() <= 0 ) {
			if (!ship.isDead)
				ship.timeLeft = booms2.getAnimationTime() * 5;
			ship.isDead = true;
			if (!ship.diedNow) {
				booms2.add(ship.getX(), ship.getY(), 0, (ship.rad * 3.5) / std::max(1., booms2.getSize() ), 1);
				ship.diedNow = true;
			}
		}
		
		// ���� ������� ����� -- �����������
		if (ship.isDead && ship.timeLeft < 0.) {
			window.close();
		}
	}

	return 0;
}