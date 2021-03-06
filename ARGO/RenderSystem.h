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
	void removeEntity(std::string ID);
	void update(SDL_Renderer *m_renderer, float dt);
	int Animate(int maxFrames, float dt);

private:
	SpriteComponent * sc;
	PositionComponent * pc;
	ControlComponent * cc;
	float time;
	int index = 0;
	int i = 0;
};