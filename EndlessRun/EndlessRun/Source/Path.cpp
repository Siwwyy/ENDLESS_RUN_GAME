#include "../Headers/Path.h"

#include <cstdlib>
#include <ctime>

#include <iostream> // test

Path::Path()
{
	srand(time(0));

	segments_.push_back({ 0, 1, 0, 0,  8, 0 });
	segments_.push_back({ 0, 2, 1, 0, 24, 0 });
	segments_.push_back({ 0, 0, 2, 0, 40, 0 });
	segments_.push_back({ 0, 0, 2, 0, 56, 0 });
	segments_.push_back({ 0, 0, 2, 7, 56 + 8, 0 });
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

		float offsetX = lastSegment.xOffset + 8 * lastSegment.rotation + (!lastSegment.rotation ? 8 : 0);

		float offsetZ = lastSegment.zOffset +(!lastSegment.rotation ? 16 : 0);

		float rotation = lastSegment.rotation;

		segments_.push_back({ 0, textureId, nextId, offsetX, offsetZ, rotation });
	}


}
