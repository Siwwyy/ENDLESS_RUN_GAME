#include "../Headers/Path.h"

#include <cstdlib>
#include <ctime>

#include <iostream> // test

const float Path::length = 16;

Path::Path()
{
	srand(time(0));

	Obstacle ob;
	Obstacle ob1;
	Obstacle ob2;
	Obstacle ob3;
	Obstacle ob4;

	segments_.push_back({ 0, 1, 0, length / 2, ob});
	segments_.push_back({ 0, 2, 1, length / 2 + length * 1, ob1});
	segments_.push_back({ 0, 0, 2, length / 2 + length * 2, ob2});
	segments_.push_back({ 0, 0, 2, length / 2 + length * 3, ob3 });
	segments_.push_back({ 0, 0, 2, length / 2 + length * 4, ob4});
}

void Path::Update(float deltaTime)
{
	int i = 0;
	for (auto &s : segments_) {

		s.zOffset -= deltaTime * 8; // todo difficulty
	
	}


	if (segments_[0].zOffset <= -length/2)
	{

		pathSegment &lastSegment = segments_.back();

		static unsigned int i = 0;

		segments_.erase(segments_.begin());

		unsigned int nextId = lastSegment.id + 1;

		unsigned int textureId = 0; //rand() % 3;


		float offsetZ = lastSegment.zOffset + length / 2;

		Obstacle ob;

		segments_.push_back({ 0, textureId, nextId, offsetZ, ob});
	}


}
