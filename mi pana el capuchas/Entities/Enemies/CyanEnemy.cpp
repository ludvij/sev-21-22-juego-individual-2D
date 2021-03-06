#include "CyanEnemy.h"
#include "Layers/GameLayer.h"
#include "Entities/Player.h"

CyanEnemy::CyanEnemy(int x, int y)
	: Enemy(CYAN_ENEMY_POS, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	m_aIdle = new Animation(CYAN_ENEMY_IDLE_POS, width, height, 18, 3, true);
	m_aDying = new Animation(CYAN_ENEMY_DEATH_POS, width, height, 18, 3, false);
	m_animation = m_aIdle;
	Health = 3;
	ShotTime = 90;
	type = "cyan";
}

Projectile* CyanEnemy::Update()
{
	Enemy::Update();
	if (state != State::MOVING) {
		Vec = { 0 };
		return nullptr;
	}
	Player* p = ((GameLayer*)Game::Get().gameLayer)->player;
	// MOVEMENT
	Vector2D dst = {x - p->x, y - p->y};

	float maxDist = (5 * Game::Get().CellSizeX * 5 * Game::Get().CellSizeY);
	float twoCell = 2 * (Game::Get().CellSizeX - Game::Get().CellSizeX / 2) * 2 * (Game::Get().CellSizeY - Game::Get().CellSizeY / 2);
	float dstSQ = dst.DistanceSquared();

	// GET CLOSE
	if (dstSQ > maxDist + twoCell) {
		Vec = -dst / std::sqrtf(dst.DistanceSquared()) * 3;
	}
	// GET FAR
	else if (dstSQ < maxDist) {
		Vec = dst / std::sqrtf(dst.DistanceSquared()) * 3;
	}
	else {
		Vec = { 0, 0 };
	}

	// SHOT
	if (ShotTime <= 0) {
		ShotTime = 90;
		auto p =  new Projectile(BASIC_PROJECTILE_POS,
			x, y, Game::Get().CellSizeX / 2, Game::Get().CellSizeY / 2, 0, 1, -dst / std::sqrtf(dst.DistanceSquared()) * 5, 1);
		p->HarmPlayer = true;
		return p;
	}
	ShotTime--;
	return nullptr;
}
