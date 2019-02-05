#include "EntityComponent.h"

class AiSystem {
public:
	void addEntity(Entity e);
	void update();
private:
	PositionComponent * posComp;
	std::vector<Entity> m_entities;

	float x = 0;
	float y = 0;
	float speed = 10;

	void checkBoundary();
	int screenWidth = 1280;
	int screenHeight = 720;

	int direction = 0;

};