#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#pragma once

#include "../Headers/Includes.h"
#include "../Headers/libs.h"

#include <chrono>
#include <random>

class Obstacle {

  public:
	enum TYPE { JUMP, SLIDE, OMIT, JUMP_WIDE, OMIT_WIDE }; // slide == wide btw

	enum POS { LEFT, CENTER, RIGHT };

	Obstacle() /*: _t("")*/ {
		unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
		std::default_random_engine generator(seed);

		_t = TYPE(generator() % 5);

		_t = (TYPE)2;

		if (_t < 3) {
			_p = POS(generator() % 3);
		} else { // type: *_WIDE
			_p = POS(generator() % 2);
		}

		// todo: texture
	}

	inline TYPE type() const { return _t; }
	inline POS pos() const { return _p; }

	// inline Texture &texture() { return _t; }

  private:
	TYPE _t;
	POS _p;

	// Texture _t;
};

#endif /* _OBSTACLE_H_ */
