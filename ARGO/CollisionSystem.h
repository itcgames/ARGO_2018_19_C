#pragma once
#include <iostream>
#include <vector>
#include"CollisionComp.h"
#include"EntityComponent.h"
#include "Animation.h"
#include "SDL.h"
#include"LTexture.h"
#include "Level.h"

class CollisionSystem
{
public:
	CollisionSystem() {};
	void addEntity(Entity e);
	void removeEntity(std::string ID);
	void setInvincible(float dt, CollisionComponent* m_collide);
	std::vector<std::string> getEntityID();
	void update(level &level, float dt);
	bool squareCollision(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2);
	bool AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2);
	void tileCollision(float x, float y, float width, float height, level &level, LifeComponent * lc);
	void Teleport(float x, float y, float width, float height, level &level);
	void CheckCollision(level &level, float dt);
	bool getInvincible();
	void resetScore(std::string id);
	void ActivateInvincible();
	
private:
	std::vector<Entity>entities;
	PositionComponent * posComp;
	PositionComponent * posComp1;
	PositionComponent * posComp2;
	SpriteComponent * spriteComp;
	AnimationComponent* ac;
	SpriteComponent * spriteComp2;
	ControlComponent* cc;
	CollisionComponent* collide;
	ScoreComponent* score;
	PickUpComponent* pickup;
	float x1, y1, x2, y2, width1, height1, width2, height2;
	float x3, y3, x4, y4, width3, height3, width4, height4;
	float time, timer;
	int count = 0;
	
};