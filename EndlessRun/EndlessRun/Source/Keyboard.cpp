#include "../Headers/Keyboard.h"

Keyboard::Keyboard()
	: Keys({ false, false, false, false }), Direction({ 0, 0 })
{
}

Keyboard::~Keyboard()
{

}

void Keyboard::Update(KeyStates k)
{
	if (k.W && k.S) {
		if (Keys.W && !Keys.S) {
			Direction.Y = -1;
		}
		if (Keys.S && !Keys.W) {
			Direction.Y = 1;
		}
	}
	else if (k.W) {
		Direction.Y = 1;
	}
	else if (k.S) {
		Direction.Y = -1;

	}
	else {
		Direction.Y = 0;
	}

	if (k.A && k.D) {
		if (Keys.D && !Keys.A) {
			Direction.X = -1;
		}
		if (Keys.A && !Keys.D) {
			Direction.X = 1;
		}
	}
	else if (k.A) {
		Direction.X = -1;
	}
	else if (k.D) {
		Direction.X = 1;
	}
	else {
		Direction.X = 0;
	}

	Keys = k;
}