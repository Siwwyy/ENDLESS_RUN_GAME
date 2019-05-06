#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle():
	Textures(NULL)
{
//	generator(rand());
}

void Obstacle::push_texture(Texture * texture)
{
	Textures.emplace_back(texture);
	//std::cout << texture << endl;
}

Texture * Obstacle::Create_Obstacle()
{
	std::random_device rand;												//do odpalenia silnika
	std::mt19937 generator(rand());											//standardowy generator (mersenne_twister_engine)
	std::uniform_int_distribution<> dis(0, (Textures.size() - 1));			//zakres naszego losowania
	if ((Textures.size() - 1) == 0)
	{
		return Textures[0];
	}
	else
	{
		return Textures[dis(generator)];
	}
}

//void Obstacle::Create_Obstacle()
//{
//	std::random_device rand;												//do odpalenia silnika
//	std::mt19937 generator(rand());											//standardowy generator (mersenne_twister_engine)
//	std::uniform_int_distribution<> dis(0, (Textures.size() - 1));			//zakres naszego losowania
//
//	//std::cout << dis(generator) << '\n';
//
//}

Obstacle::~Obstacle()
{
	Textures.clear();
}
