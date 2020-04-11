//global.h
#include "SFML/Graphics.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>

#ifndef __GLOBAL_H__ 
#define __GLOBAL_H__ 

namespace global {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const double SHIP_ACCELERATION = 0.0002;
	const double SHIP_DECELERATION = 0.0006;
	const double SHIP_ROTATION_SPEED = 0.1;

	const double SHIP_SCALE = 0.5;

	const double PI = std::atan2(0., -1.);

	const double SHIP_RATE_OF_FIRE = 400.;
	const double ENEMY_RATE_OF_FIRE = 3000.;

	const double SHIP_BULLET_SPEED = 0.5;
	const double ENEMY_BULLET_SPEED = 0.7;

	const double ENEMY_SHOOT_RAD = 400.;

	const double SCALE = 0.6;

	const double ASTEROID_HP_FACTOR = 2;
	const double ENEMY_HP_FACTOR = 3;
	const double COLLISION_FACTOR = 0.3;
	const double SPEED_DAMAGE_FACTOR = 150.;
	const int SHIP_HP = 500;
}

enum GDirection { Down, Left, Right, Up };

#endif