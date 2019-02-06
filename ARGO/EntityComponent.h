#pragma once
#include <vector>
#include "Component.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "ControlComponent.h"
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include <string>
#include <iostream>
#include <sdl.h>

class Entity
{
	int id;
public:
	Entity(std::string name): m_name(name) {};
	void addComponent(Component* c) {

		components.push_back(c);
	}
	Component * getCompByType(std::string name) {
		for (Component * comp : components) {
			if (comp->getID() == name ) {
				return comp;
			}
		}
	}
	void removeComponent(Component* c) {
		/*TBI*/
	}
	std::vector<Component*> getComponents() {

		return components;
	}
	std::string getName() {

		return m_name;
	}
private:
	std::vector<Component*> components;
	std::string m_name;
};