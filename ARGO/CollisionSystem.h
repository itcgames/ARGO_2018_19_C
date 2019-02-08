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
	bool squareCollision(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2);
	void CheckCollision();
private:
	std::vector<Entity>entities;
	PositionComponent * posComp;
	PositionComponent * posComp1;
	SpriteComponent * spriteComp;
	ControlComponent* cc;
	CollisionComponent* collide;
	float x1, y1, x2, y2, width1, height1, width2, height2;
};