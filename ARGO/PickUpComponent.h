#pragma once
#include "Component.h"
#include "AudioManager.h"



class PickUpComponent : public Component
{
public:
	PickUpComponent() {}
	std::string getID()
	{
		return id;
	}


	enum PickUp {
		Collectable,
		NotCollectable
	};


	void setState(PickUp state) {
		m_currentState = state;
	};
	PickUp getState() {
		return m_currentState;
	}
	PickUp m_currentState = Collectable;

private:
	std::string id = "PickUp";


};

