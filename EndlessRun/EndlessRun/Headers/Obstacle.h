#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#pragma once

#include "../Headers/Includes.h"
#include "../Headers/libs.h"

#include <chrono>
#include <random>

class Obstacle {

  public:
	enum POS_VER { TOP, MIDDLE, BOTTOM, TOP_MIDDLE_BOTTOM, TOP_MIDDLE, MIDDLE_BOTTOM };

	enum POS_HOR { LEFT, CENTER, RIGHT, LEFT_MIDDLE_RIGHT, LEFT_MIDDLE, MIDDLE_RIGHT };

	Obstacle() /*: _t("")*/ {
		unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
		std::default_random_engine generator(seed);
		_pv = POS_VER(generator() % MIDDLE_BOTTOM + 1);
		_ph = POS_HOR(generator() % MIDDLE_RIGHT + 1);

		// todo: texture
	}

	inline POS_HOR ph() { return _ph; }
	inline POS_VER pv() { return _pv; }

	//inline Texture &texture() { return _t; }

  private:
	POS_HOR _ph;
	POS_VER _pv;
	//Texture _t;
};

#endif /* _OBSTACLE_H_ */
