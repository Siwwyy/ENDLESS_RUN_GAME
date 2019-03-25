#include "../Headers/Path.h"

#include <cstdlib>
#include <ctime>

#include <iostream> // test

Path::Path()
{
	srand(time(0));

	segments_.push_back({ 0, 1, 0, 8 });
	segments_.push_back({ 0, 2, 1, 24 });
	segments_.push_back({ 0, 0, 2, 40 });
}

void Path::Update(float deltaTime)
{

	for (auto &s : segments_) { s.zOffset -= deltaTime * 8; }


	if (segments_[0].zOffset <= -8)
	{
		static unsigned int i = 0;
		segments_.erase(segments_.begin());

		unsigned int nextId = segments_.back().id + 1;

		//unsigned int textureId = rand() % 3;
		unsigned int textureId = 0;

		float offset = segments_.back().zOffset + 16;

		segments_.push_back({ 0, textureId, nextId, offset });
	}


}