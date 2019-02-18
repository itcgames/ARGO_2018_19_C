#pragma once
#include <vector>
#include "Component.h"
#include "Projectile.h"

class AmmoComponent : public Component
{

public:
	AmmoComponent(SDL_Renderer* m_renderer):renderer(m_renderer) {};
	std::vector<Projectile *> projectiles;
	
	/*Data only*/
	float getPositionX() {
		return positionX;
	}

	float getPositionY() {
		return positionY;
	}


	void setPosition(float x, float y) {
		this->positionX = x;
		this->positionY = y;
	}

	float getAmmo() {
		return ammoCount;
	}
	void setAmmo(float ammo) {
		 ammoCount = ammo;
	}

	std::string getID()
	{
		return id;
	}
	
	void dropProjectile(float x, float y) {

		projectiles.push_back(new Projectile(x, y, renderer));
	}

	void render() {
		for (std::vector<int>::size_type i = 0; i != projectiles.size(); i++) {
			/* std::cout << v[i]; ... */
			projectiles[i]->render(renderer);
		}
	}

	void checkCollision(float playerX, float playerY)
	{
		if (projectiles.size() > 0)
		{
			for (std::vector<int>::size_type i = projectiles.size() - 1; i <= 0; i--) {

				float proX = projectiles[i]->getPositionX();
				float proY = projectiles[i]->getPositionY();
				float proW = projectiles[i]->getWidth();
				float proH = projectiles[i]->getHeight();
				//can hardcode w = 80 h 100


				if (proX < playerX + 80 &&
					proX + proW > playerX &&
					proY < playerY + 100 &&
					proX + proY > playerY) {
					// collision detected!
					std::cout << "collision" << std::endl;

					projectiles.erase(projectiles.begin() + i);

				}
			}
		}

	}
	
	
private:
	float positionX;
	float positionY;
	std::string  id = "Ammo";
	int ammoCount= 0;
	LTexture m_texture;
	SDL_Renderer* renderer;

};