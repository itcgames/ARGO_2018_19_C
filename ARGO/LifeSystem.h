#pragma once
#include <iostream>
#include <vector>
#include "LifeComponent.h"
#include"EntityComponent.h"
#include "SDL.h"
#include "LTexture.h"


class LifeSystem
{
public:
	LifeSystem();
	void addEntity(Entity e);
	void removeEntity(std::vector<Entity>&entities, std::string ID);

	void update();


private:
	//Game* m_game;
	std::vector<Entity>entities;
	std::vector<Entity>deadEntities;
	PositionComponent * posComp;
	PositionComponent * posComp1;
	PositionComponent * posComp2;
	SpriteComponent * spriteComp;
	SpriteComponent * spriteComp2;
	ControlComponent* cc;
	CollisionComponent* collide;
	ScoreComponent* score;
	PickUpComponent* pickup;
	float x1, y1, x2, y2, width1, height1, width2, height2;
	float x3, y3, x4, y4, width3, height3, width4, height4;
	float time;
};