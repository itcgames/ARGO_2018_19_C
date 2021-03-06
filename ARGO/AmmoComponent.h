#pragma once
#include <vector>
#include "Component.h"
#include "Projectile.h"
#include "SeekerProjectile.h"


class AmmoComponent : public Component
{

public:
	AmmoComponent(SDL_Renderer* m_renderer):renderer(m_renderer) {};
	std::vector<Projectile *> projectiles;
	std::vector<Seeker *> seekers;

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

	float getClosest(float x, float y) {
		//pass current entity pos and compare seeker[i] pos

		 for (std::vector<int>::size_type i = 0; i != seekers.size(); i++) {

			closestDis = sqrt((x - seekers[i]->getPositionX())*(x - seekers[i]->getPositionX())
				 + (y - seekers[i]->getPositionY())*(y - seekers[i]->getPositionY()));

			
		 }

		 return closestDis;
	}
	void setClosest(float dis) {
		closestDis = dis;
	}

	float getSeekerAmmo() {
		return seekerCount;
	}
	void setSeekerAmmo(float seekerAmmo) {
		seekerCount = seekerAmmo;
	}

	std::string getID()
	{
		return id;
	}
	
	void dropProjectile(float x, float y) {
		projectiles.push_back(new Projectile(x, y, renderer));
	}

	void dropSeeker(float x, float y, int life) {

		seekers.push_back(new Seeker(x, y, renderer));
	}

	void deleteProjectile(int index) {
		//pass the index 
		projectiles.erase(projectiles.begin() + index);
	}

	void deleteSeeker(int index) {
		//pass the index 
		seekers.erase(seekers.begin() + index);
	}

	void render() {
		for (std::vector<int>::size_type i = 0; i != projectiles.size(); i++) {
			/* std::cout << v[i]; ... */
			projectiles[i]->render(renderer);
		}

		for (std::vector<int>::size_type i = 0; i != seekers.size(); i++) {
			/* std::cout << v[i]; ... */
			seekers[i]->render(renderer);
		}
	}

	void seek(float x, float y) {

		for (std::vector<int>::size_type i = 0; i != seekers.size(); i++) {

			// x & y flag == playerPosition
			// seekers[i]->x & seekers[i]->y projectile == m_position

			float m_velocityX;
			float m_velocityY;
			float m_velocityF;
			float m_maxSpeed = 1.5f;
			//m_velocity = playerPosition - m_position;
			m_velocityX = x - seekers[i]->getPositionX();
			m_velocityY = y - seekers[i]->getPositionY();
			//Get magnitude of vector
			m_velocityF = std::sqrt(m_velocityX*m_velocityX + m_velocityY * m_velocityY);

			//Normalize vector
			m_velocityX = m_velocityX / m_velocityF;
			m_velocityY = m_velocityY / m_velocityF;

			m_velocityX = m_velocityX * m_maxSpeed;
			m_velocityY = m_velocityY * m_maxSpeed;

			//m_position = m_position + m_velocity;
			float newX = seekers[i]->getPositionX() + m_velocityX;
			float newY = seekers[i]->getPositionY() + m_velocityY;
			seekers[i]->setPosition(newX, newY);
		}
		
	}

	bool checkCollision(float playerX, float playerY)
	{
		if (projectiles.size() > 0)
		{
			for (std::vector<int>::size_type i = projectiles.size() - 1; i <= 0; i--) {

				float proX = projectiles[i]->getPositionX();
				float proY = projectiles[i]->getPositionY();
				float proW = projectiles[i]->getWidth();
				float proH = projectiles[i]->getHeight();
				//can hardcode w = 80 h 100


				if (proX < playerX + 40 &&
					proX + proW > playerX &&
					proY < playerY + 50 &&
					proY + proH > playerY) {
					// collision detected!
					std::cout << "collision" << std::endl;

					//int j = projectiles.size() -  i; 
					projectiles.erase(projectiles.begin() + i);
					return true;
				}
			}
		}
		//seeker collision
		if (seekers.size() > 0)
		{
			for (std::vector<int>::size_type i = seekers.size() - 1; i <= 0; i--) {

				float seekX = seekers[i]->getPositionX();
				float seekY = seekers[i]->getPositionY();
				float seekW = seekers[i]->getWidth();
				float seekH = seekers[i]->getHeight();

				//can hardcode w = 80 h 100
				//will have to change after merge

				if (seekX < playerX + 40 &&
					seekX + seekW > playerX &&
					seekY < playerY + 50 &&
					seekY + seekH > playerY) {
					// collision detected!
					std::cout << "seeker collision" << std::endl;
					
					seekers.erase(seekers.begin() + i);
					return true;
				}
			}
		}
		return false;

	}
	
	
private:
	float positionX;
	float positionY;
	std::string  id = "Ammo";
	int ammoCount= 0;
	int seekerCount = 0;
	LTexture m_texture;
	SDL_Renderer* renderer;
	float closestDis = 10000;


};