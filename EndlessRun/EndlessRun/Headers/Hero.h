#ifndef _HERO_H_
#define _HERO_H_
#pragma  once

#include "Includes.h"

class Hero
{
public:
	Hero();

	void update(float deltaTime, short mx, short my); // mx, my: -1 / 0 / 1
	std::pair<float, float> getPosition() const { return Position; }
	//std::pair<float, float> getVelocity()const { return Velocity; }

	inline float getWidth() const { return Height; }
	inline float getHeight() const { return Width; }


private:
	std::pair<float, float> Position; // {x, y}
	std::pair<float, float> Velocity; // {x, y}, predkosc

	float Width, Height;
};

#endif  /* _HERO_H_ */