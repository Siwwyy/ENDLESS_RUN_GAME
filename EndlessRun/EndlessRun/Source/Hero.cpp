#include "../Headers/Includes.h"
#include "../Headers/libs.h"

Hero::Hero()
	: Width(1), Height(1), Position({0.0f, -0.75f})
{

}

void Hero::update(float deltaTime, short mx, short my)
{
	Position.first += mx * deltaTime;
	Position.second += my * deltaTime;
}