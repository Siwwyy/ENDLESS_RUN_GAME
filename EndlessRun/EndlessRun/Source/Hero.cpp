#include "../Headers/Includes.h"
#include "../Headers/libs.h"

Hero::Hero()
	: Width(1), Height(1), Position({ 0.0f, -0.75f }), Velocity({0.0f, 0.0f})
{

}

void Hero::update(float deltaTime, short mx, short my)
{
	// Turning
	Position.first += mx * deltaTime;

	// Jumping
	float G = -9.8f;

	if (my == 1 && Position.second == 0) // jump on pressing W
		Velocity.second = 5;
	

	if (my == -1 && Position.second > 0)  // dash downward on pressing S
		Velocity.second = -6;
	

	Position.second = Position.second + deltaTime * Velocity.second; // calculate player posision
	
	if (Position.second > 1)  // prevent player from jumping too high
		Position.second = 1;
	

	Velocity.second = Velocity.second + deltaTime * G; // update velocity

	if (Position.second <= 0) { // prevent player from falling through path
		Position.second = 0;
		Velocity.second = 0;
	}

	// Sliding
	// todo
}