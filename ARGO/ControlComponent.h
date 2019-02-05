#pragma once
#include "Component.h"



class ControlComponent : public Component
{
public:
	ControlComponent() {}
	std::string getID()
	{
		return id;
	}
	

	enum Direction {
		Idle,
		Left,
		Right,
		Up,
		Down
	};
	

	void setDirection(Direction state) {
		m_currentDirection = state;
	};
	Direction getDirection() {
		return m_currentDirection;
	}

private:
	std::string id = "Control";
	Direction m_currentDirection = Idle;

};

