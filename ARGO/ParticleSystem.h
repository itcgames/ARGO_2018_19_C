#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"

class ParticleSystem
{
	std::vector<Entity> entities;
	Particle* particles[10];

public:
	void initialise() {
		for (int i = 0; i < 10; ++i)
		{
			particles[i] = new Particle(0, 0);
		}
	}
	void addEntity(Entity e) {
		/*TBI*/
		entities.push_back(e);

	}
	void update(SDL_Renderer *m_renderer) {
		//std::cout << "Particle SYSTEM: " << std::endl;

		int index = 0;
		

		/* Loop through Entities with */
		for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component * component : entity.getComponents()) {
		

				//ParticleComponent * partComp = (ParticleComponent*)entity.getCompByType("Particle");
				PositionComponent * posComp = (PositionComponent*)entity.getCompByType("Position");

				float mPosX = posComp->getPositionX();
				float mPosY = posComp->getPositionY();
		
				//pick a colour and render
				for (int i = 0; i < 10; ++i)
				{
					particles[i]->Init(m_renderer);
					particles[i]->render(m_renderer);
				}

				//Go through particles
				for (int i = 0; i < 10; ++i)
				{
					//Delete and replace dead particles
					if (particles[i]->isDead())
					{
						delete particles[i];
						particles[i] = new Particle(mPosX, mPosY);
					}
				}
			}
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
};