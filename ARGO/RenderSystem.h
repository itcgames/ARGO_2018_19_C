#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"


class RenderSystem
{
	std::vector<Entity> entities;

public:
	RenderSystem();
	void addEntity(Entity e);
	void update(SDL_Renderer *m_renderer, float dt);

private:
	SpriteComponent * sc;
	PositionComponent * pc;
	float time;
	int index = 0;
};