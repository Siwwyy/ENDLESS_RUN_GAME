#include "../Headers/Includes.h"
#include "../Headers/libs.h"

#include <cmath>

Hero::Hero()
	: Width(1), Height(1), Position({ 0.0f, -0.75f }), Velocity({0.0f, 0.0f})
{
}

void Hero::update(float deltaTime, short mx, short my)
{
	// Turning		
	if (mx == 1 && Velocity.first <= 0)  // go left on pressing A
		Velocity.first = 1;

	if (mx == -1 && Velocity.first >= 0) // go right on pressing D
		Velocity.first = -1;
	
	Velocity.first *= 1.3f; // update velocity
	float deltaX = deltaTime * Velocity.first;
	Position.first += deltaX; // update player posision
	
	 // stop if player hit right / center / left point
	if (Position.first > 1) {
		Position.first = 1;
		Velocity.first = 0;
	}
	if (Position.first < -1) {
		Position.first = -1;
		Velocity.first = 0;
	}
	if (abs(Position.first) < abs(deltaX)) {
		Position.first = 0;
		Velocity.first = 0;
	}

	// Jumping
	float G = -9.8f; // gravity

	if (my == 1 && Position.second == 0) // jump on pressing W
		Velocity.second = 5;
	

	if (my == -1 && Position.second > 0)  // dash downward on pressing S
		Velocity.second = -6;
	

	float deltaY = deltaTime * Velocity.second;
	Position.second += deltaY; // uodate player posision
	
	//if (Position.second > 1)  // prevent player from jumping too high
	//	Position.second = 1;
	

	Velocity.second = Velocity.second + deltaTime * G; // update velocity

	if (Position.second <= 0) { // prevent player from falling through path
		Position.second = 0;
		Velocity.second = 0;
	}

	// Sliding
	// todo
}