#ifndef _PATH_H_
#define _PATH_H_
#pragma once

//#include "Includes.h"
#include "libs.h"

#include <vector>

struct pathSegment 
{
	unsigned int type;
	unsigned int textureId;
	unsigned int id;
	// unsigned int obstacleType;
	// bool hasCoins; ?
	float zOffset;
};

class Path
{
public:

	enum  SEGMENT { // pathSegment.type
		REGULAR,
		TURN_LEFT,
		TURN_RIGHT,
		TURN_T
	};

	enum TEXTURE { // pathSegment.textureId
		BRICK1,
		BRICK2,
		BRICK3
	};

	// jedna przeszkoda na segment? po srodku? jeszcze jeden enum dla umiejscowienia przeszkody?
	// co z lancuchami monet?
	//enum OBSTACLE_TYPE {
	//	NONE,
	//	LOG,
	//	ROCK_LEFT,
	//	ROCK_CENTER,
	//	ROCK_RIGHT
	//};

	Path();

	void Update(float deltaTime);

	inline unsigned int getLength() { return segments_.size(); }

	inline const pathSegment & operator[](int i) {
		return segments_[i];
	}


private:
	std::vector<pathSegment> segments_;

	float oldTime;
	float newTime;
};

#endif /* _PATH_H_ */