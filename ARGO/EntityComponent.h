#pragma once
#include <vector>
#include "Component.h"
#include "LifeComponent.h"
#include "PositionComponent.h"
#include "ControlComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "CollisionComp.h"
#include "ParticleComponent.h"
#include "ScoreComponent.h"
#include "PickUpComponent.h"
#include "Velcomponent.h"
#include "AmmoComponent.h"
#include "AiComponent.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sdl.h>

class Entity
{
	int id;
public:
	Entity(std::string name): m_name(name) {};
	void addComponent(Component* c)
	{
		components.push_back(c);
	}
	Component * getCompByType(std::string name) {
		for (Component * comp : components) {
			if (comp->getID() == name ) {
				return comp;
			}
		}
		return nullptr;
	}
	void removeComponent(Component* c) {
		/*TBI*/
	}
	std::vector<Component*> getComponents() {

		return components;
	}
	std::string getName()
	{
		return m_name;
	}
private:
	std::vector<Component*> components;
	std::string m_name;
};
