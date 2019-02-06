#pragma once
#include <iostream>
#include <vector>
#include"CollisionComp.h"
#include"EntityComponent.h"
#include "SDL.h"
#include"LTexture.h"

class CollisionSystem
{
public:
	CollisionSystem() {};
	void addEntity(Entity e);
	void update();
	void CheckCollision();
private:
	std::vector<Entity>entities;
	PositionComponent* posComp;
	SpriteComponent * spriteComp;
	CollisionComponent* collide;
	float x1, y1, x2, y2, width1, height1, width2, height2;
};