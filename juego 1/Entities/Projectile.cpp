#include "Projectile.h"

Projectile::Projectile(std::string_view filename, int x, int y, int width, int height, float angle, int pierce, Vector2D velocity)
	: Entity(filename, x, y, width, height),
	  Pierce(pierce),
	  Angle(angle)
{
	Vec = velocity;
}

void Projectile::Draw(float scrollX)
{
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = m_texSize.x;
	source.h = m_texSize.y;
	// tama�o de la entidad
	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(Game::Get().Renderer, m_texture, &source, &destination, Angle, nullptr, SDL_FLIP_NONE);
#ifdef OUTLINE
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0xffffffff));
	SDL_RenderDrawRect(Game::Get().Renderer, &destination);
	SDL_SetRenderDrawColor(Game::Get().Renderer, HEX_COLOR(0));
#endif
}

void Projectile::Update()
{
	if (Pierce == 0)
		Deleted = true;
	if (Vec.x == 0 && Vec.y == 0)
		Deleted = true;
}

bool Projectile::IsOverlap(Entity* entity)
{
	if (Entity::IsOverlap(entity)) {
		if (entity->Pierceable) {
			for (auto itr = m_pierced.begin(); itr != m_pierced.end(); itr++) {
				Entity* e = *itr;
				if (*e == *entity) {
					return true;
				}
			}
			m_pierced.push_back(entity);
			Pierce--;
		}

	}

	return false;
}
