#include "../Headers/Path.h"

#include <cmath>
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
	segments_.push_back({ 0, 0, 2, 7, 56 + 8, 1 });
}

void Path::Update(float deltaTime)
{

	for (int i = 1; i <= segments_.size() ; ++i) {
		pathSegment &s = segments_[i-1];

		s.zOffset -= deltaTime * 8;

		// automatyczne obracanie
		bool shouldRotate = s.rotation || segments_[i - 1].rotation;


		if (s.zOffset < 10 && shouldRotate) {
			s.rotation *= 0.96;

			if (abs(s.rotation) < 0.001f) {
				s.rotation = 0.0f;
				//s.xOffset = 0;
			}
		}

	}

	if (segments_[0].zOffset + abs(segments_[0].xOffset) <= -8)
	{

		pathSegment &lastSegment = segments_.back();

		static unsigned int i = 0;

		segments_.erase(segments_.begin());

		unsigned int nextId = lastSegment.id + 1;

		unsigned int textureId = 0; //rand() % 3;

		float offsetX = lastSegment.xOffset + 8 * lastSegment.rotation + (!lastSegment.rotation ? 8 : 0);

		float offsetZ = lastSegment.zOffset + (!lastSegment.rotation ? 16 : 0);

		if (lastSegment.xOffset && !lastSegment.rotation) {
			offsetZ += lastSegment.xOffset;
		}


		float rotation = lastSegment.rotation;

		segments_.push_back({ 0, textureId, nextId, offsetX, offsetZ, rotation });
	}


}
