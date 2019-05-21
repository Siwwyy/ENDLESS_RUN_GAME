#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#pragma once

#include "../Headers/Includes.h"
#include "../Headers/libs.h"

#include <chrono>
#include <random>

class Obstacle {

  public:
	enum TYPE { JUMP_OVER, SLIDE, OMIT_WIDE, JUMP_OVER_WIDE, SLIDE_WIDE }; // w=3 dla slide_wide, w=2 dla pozostaych _wide
	enum PH { LEFT = -1, CENTER = 0, RIGHT = 1 };

	Obstacle() /*: _t("")*/ {
		unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
		std::default_random_engine generator(seed);

		_type = TYPE(generator() % 5);

		while (_type == SLIDE || _type == SLIDE_WIDE) { // test
			_type = TYPE(generator() % 5);
		}
		
		if (_type < 2) { // JUMP_OVER, SLIDE
			_pos = PH((generator() % 3)-1);
		}
		else if (_type != SLIDE_WIDE) { // OMIT_WIDE, JUMP_OVER_WIDE
			_pos = PH((generator() % 2)-1);

		}
		else { // SLIDE_WIDE
			_pos = CENTER;
		}

		// todo: texture
	}

	// inline POS_HOR ph() { return _ph; }
	inline TYPE type() const { return _type; }
	inline PH pos() const { return _pos; }

	// inline Texture &texture() { return _t; }

  private:
	TYPE _type;
	PH _pos;

	// Texture _t;
};

#endif /* _OBSTACLE_H_ */
