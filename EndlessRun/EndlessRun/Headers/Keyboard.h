#pragma once

struct KeyStates
{
	bool W;
	bool S;
	bool A;
	bool D;

	void operator=(const KeyStates& k) {
		W = k.W;
		A = k.A;
		S = k.S;
		D = k.D;
	}

};

class Keyboard
{
private:
	KeyStates Keys;

	struct {
		short X = 0;
		short Y = 0;
	} Direction;

public:
	Keyboard();
	~Keyboard();

	void Update(KeyStates k);
	inline short getDirX() { return Direction.X; }
	inline short getDirY() { return Direction.Y; }
};