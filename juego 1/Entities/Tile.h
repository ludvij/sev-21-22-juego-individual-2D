#pragma once
#include "Entity.h"
class Tile : public Entity
{
public:
	Tile(std::string filename, int x, int y);

	bool isPointInBounds(int x, int y);
};


