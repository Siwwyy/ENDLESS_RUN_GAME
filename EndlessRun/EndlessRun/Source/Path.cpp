#include "../Headers/Path.h"

#include <cstdlib>
#include <ctime>

#include <iostream> // test

Path::Path()
{
	srand(time(0));

	Obstacle ob;
	Obstacle ob1;
	Obstacle ob2;
	Obstacle ob3;
	Obstacle ob4;

	segments_.push_back({ 0, 1, 0, 0,  8, ob, 0 });
	segments_.push_back({ 0, 2, 1, 0, 24, ob1, 0 });
	segments_.push_back({ 0, 0, 2, 0, 40, ob2, 0 });
	segments_.push_back({ 0, 0, 2, 0, 56, ob3, 0 });
	segments_.push_back({ 0, 0, 2, 7, 56 + 8, ob4, 0 });
}

void Path::Update(float deltaTime)
{
	int i = 0;
	for (auto &s : segments_) {

		s.zOffset -= deltaTime * 8;

		// todo automatyczne obracanie
		//bool shouldRotate = s.rotation || segments_[i+1].rotation;

		//if (s.zOffset < 10 && shouldRotate) {
		//	s.rotation -=  s.rotation ? 0.006 : 0.002;
		//	s.xOffset *= 0.99;
		//}

		//++i;
	
	}


	if (segments_[0].zOffset <= -8)
	{

		pathSegment &lastSegment = segments_.back();

		static unsigned int i = 0;

		segments_.erase(segments_.begin());

		unsigned int nextId = lastSegment.id + 1;

		unsigned int textureId = 0; //rand() % 3;

		float offsetX = lastSegment.xOffset + 8 * lastSegment.rotation;// + (!lastSegment.rotation ? 8 : 0);

		float offsetZ = lastSegment.zOffset + 8; // (!lastSegment.rotation ? 16 : 0);

		Obstacle ob;

		float rotation = lastSegment.rotation;

		segments_.push_back({ 0, textureId, nextId, offsetX, offsetZ, ob, rotation });
	}


}
