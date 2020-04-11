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

// функиця перемещающая камеру в указанные координаты
void getPlayerCoordinateForView(double x, double y) {
	myView.setCenter(x, y);
}

// объявляем автероиды и врагов
Asteroids asteroids;
Enemys enemys;

// генерируем объекты на карте
void generateMap() {
	int NUMBER = 3000; // радиус, в котором будут генерироваться объекты

	// генерация астероидов
	bool f = false;
	int k = 300 + rand() % 100, x, y;
	for (int i = 0; i < k; ++i) {
		do {
			// генерируем случайные координаты
			x = -NUMBER + rand() % (2 * NUMBER);
			y = -NUMBER + rand() % (2 * NUMBER);

			// проверяем на возможное пересечение с другими
			f = false;
			for (int i = 0; i < asteroids.cnt; i++) {
				Vector2f delta = ((Vector2f)asteroids.list[i].pos - Vector2f(x, y));
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
				if (len < 2.2 * asteroids.list[i].rad) {
					f = true;
				}
			}
		// в цикле проверка координат -- чтобы не далеко, но и не в самом центре
		} while (x * x + y * y > NUMBER * NUMBER || x * x + y * y < 200 * 200 || f);
		asteroids.add(x, y); // собственно добавляем
	}

	// генерация врагов (аналогично астероидам)
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

	srand(time(NULL)); // рандом каждый раз разный

	Clock clock;

	Menu menu;

	// загружаем  шрифт и спрайты из файлов, для спрайтов задаем мастаб
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

	Booms booms, booms2; // взрывы лазеров и взрывы уничтожения
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

	while (window.isOpen())  //Пока окно открыто
	{
		float time = clock.getElapsedTime().asMicroseconds(); // дать прошедшее время в микросекундах
		clock.restart(); // перезагружает время
		time = time/800; // скорость игры
		//std::cout << time << "\n"; // смотрим как живет время (перезагружается, как видим)
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

		sf::Event event;
		while (window.pollEvent(event)) // Закрытие окна
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
		
		ship.update(time); // обновляем состояние корабля (время с последнего выстрела)
		enemys.update(time);
		ship.checkKeyboard(time); // управление

		ship.shoot(&bullets); // стреляем
		enemys.shoot(&bullets, &ship); // стреляем

		// проверяем столкновение корабля и астероидов
		for (int i = 0; i < asteroids.cnt; i++) {
			Vector2f delta = ((Vector2f)asteroids.list[i].pos - ship.getNextPos(time));
			double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // дистанция между объектами
			if (len < ship.rad + asteroids.list[i].rad) {
				if (asteroids.list[i].hp > 0) {
					asteroids.list[i].hp -= ship.getSpeed() * SPEED_DAMAGE_FACTOR; // наносим урон столкновением
					ship.scaleSpeed(-global::COLLISION_FACTOR); // изменяем скорость корабля
					ship.setAc(-global::SHIP_ACCELERATION); // изменяем ускорение корабля
				}
			}
		}

		// проверяем столкновение пуль и астероидов
		for (int i = 0; i < bullets.cnt; i++) {
			Vector2f bulNextPos = bullets.getNextPos(time, i);
			for (int j = 0; j < asteroids.cnt; j++) {
				Vector2f delta = ((Vector2f)asteroids.list[j].pos - bulNextPos);
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // дистанция между объектами
				if (len < asteroids.list[j].rad) {
					bullets.list[i].isDead = true; // убиваем пулю
					booms.add(bulNextPos.x, bulNextPos.y, bullets.list[i].type, booms.scaleX, 2); // создаем лазерный взрыв
					asteroids.list[j].hp -= bullets.list[i].damage; // наносим урон от пули

					if (asteroids.list[j].hp <= 0 && bullets.list[i].type == 0) { // если астероид погиб и это пуля игрока
						ship.addScore(asteroids.list[j].rad * 5); // изменяем счет
					}
				}
			}
		}

		// проверяем столкновение пуль и врагов
		for (int i = 0; i < bullets.cnt; i++) {
			Vector2f bulNextPos = bullets.getNextPos(time, i);
			for (int j = 0; j < enemys.cnt; j++) {
				Vector2f delta = ((Vector2f)enemys.list[j].pos - bulNextPos);
				double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // дистанция между объектами
				if (len < enemys.list[j].rad && bullets.list[i].owner != j) { // дополнительная проверка: пуля не сталкивается с тем, кто ее выпустил
					bullets.list[i].isDead = true; // убиваем пулю
					booms.add(bulNextPos.x, bulNextPos.y, bullets.list[i].type, booms.scaleX, 2); // создаем лазерный взрыв
					enemys.list[j].hp -= bullets.list[i].damage; // наносим урон от пули
					
					if (enemys.list[j].hp <= 0 && bullets.list[i].type == 0) { // если враг погиб и это пуля игрока
						ship.addScore(enemys.list[j].rad * 10); // изменяем счет
					}
				}
			}
		}

		// проверяем столкновение корабля и врага
		for (int i = 0; i < enemys.cnt; i++) {
			Vector2f delta = ((Vector2f)enemys.list[i].pos - ship.getNextPos(time));
			double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // дистанция между объектами
			if (len < ship.rad + enemys.list[i].rad) {
				if (enemys.list[i].hp > 0) {
					enemys.list[i].hp -= ship.getSpeed() * SPEED_DAMAGE_FACTOR; // наносим урон столкновением
					ship.scaleSpeed(-global::COLLISION_FACTOR); // изменяем скорость корабля
					ship.setAc(-global::SHIP_ACCELERATION); // изменяем ускорение корабля
				}
			}
		}

		// проверяем столкновение корабля и пуль
		for (int i = 0; i < bullets.cnt; i++) {
			Vector2f bulNextPos = bullets.getNextPos(time, i);
			Vector2f delta = ((Vector2f)bullets.list[i].pos - ship.getNextPos(time));
			double len = sqrt((delta.x * delta.x) + (delta.y * delta.y)); // дистанция между объектами
			if (len < ship.rad && bullets.list[i].owner != -1) { // дополнительная проверка: пуля не сталкивается с тем, кто ее выпустил
				ship.takeDamage(bullets.list[i].damage); // наносим урон от пули
				bullets.list[i].isDead = true; // убиваем пулю
				booms.add(bulNextPos.x, bulNextPos.y, bullets.list[i].type, booms.scaleX, 2); // создаем лазерный взрыв
			}
		}
		
		// перемещения 
		if (ship.getHp() > 0)
			ship.move(time);
		asteroids.move(time); 
		bullets.move(time);

		// обновляем анимацию
		background.update(&ship);
		booms.updateAnimation(time);
		booms2.updateAnimation(time);
		enemys.updateAnimation(time);
		ship.updateAnimation(time);

		// проверяем на живучесть
		booms.check();
		booms2.check();
		enemys.check(&booms2);
		asteroids.check(&booms2);

		// перемещаем камеру на корабль
		getPlayerCoordinateForView(ship.getX(), ship.getY());

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		window.setView(myView); // ставим камеру
		window.clear(); // чистим!
		
		menu.update(&ship);

		// отрисовываем объекты
		background.draw(&window);
		asteroids.draw(&window);
		bullets.draw(&window);
		enemys.draw(&window);
		if (!ship.isDead || !ship.timeLeft < 0)
			ship.draw(&window);
		booms.draw(&window);
		booms2.draw(&window);
		menu.draw(&window);

		window.display(); //Показываем нарисованное на экране

		// удаляем мертвые объекты
		bullets.removeDead();
		booms.removeDead();
		booms2.removeDead();
		asteroids.removeDead();
		enemys.removeDead();

		// проверка корабля на конец игры
		if (ship.getHp() <= 0 ) {
			if (!ship.isDead)
				ship.timeLeft = booms2.getAnimationTime() * 5;
			ship.isDead = true;
			if (!ship.diedNow) {
				booms2.add(ship.getX(), ship.getY(), 0, (ship.rad * 3.5) / std::max(1., booms2.getSize() ), 1);
				ship.diedNow = true;
			}
		}
		
		// если корабль мертв -- завершаемся
		if (ship.isDead && ship.timeLeft < 0.) {
			window.close();
		}
	}

	return 0;
}