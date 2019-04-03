#ifndef _PATH_H_
#define _PATH_H_
#pragma once

//#include "Includes.h"
#include "libs.h"

#include <vector>

struct pathSegment 
{
	unsigned int type; // 0 = regular, 1 = turn, ...
	unsigned int textureId; // 1 = kot.png, 2 = kot2.png, 3 = rogacz.png
	unsigned int id;
	float xOffset;
	float zOffset;
	float rotation; // [-1, 1], 0 = normal  
};

class Path
{
public:

	enum { // segment types
		REGULAR
	};

	enum { // segment textures
		CAT1 = 1,
		CAT2 = 2,
		DEER = 3
	}; 

	void Update(float deltaTime);
	Path();


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