#include "TripleWand.h"


TripleWand::TripleWand(int x, int y)
	: Weapon("rcs/player/weapons/weapon_triple_wand.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	shotTime = 30;
	projectileSpeed = 10;
}

std::list<Projectile*> TripleWand::Use()
{
	std::list<Projectile*> res;
	if (Ready == true) {
		Ready = false;
		for (int i = 0; i < 3; i++) {
			// sdl uses degree but c++ uses radians
			float angle = (Angle - 15 * (i - 1))/ 180.0f * static_cast<float>(M_PI);
			Vector2D vel = { std::cosf(angle),std::sinf(angle) };
			vel = -vel * projectileSpeed;
			res.push_back(new Projectile("rcs/player/weapons/projectile_triple_wand.png", x, y, width / 1.5f, height / 1.5f, Angle, 1, vel));
		}
	}
	return res;
}

void TripleWand::Update()
{
	if (!Ready) shotTime--;
	if (shotTime <= 0) {
		Ready = true;
		shotTime = 30;
	}
}
