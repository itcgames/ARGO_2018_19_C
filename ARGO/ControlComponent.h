#pragma once
#include "Component.h"
#include "AudioManager.h"



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
	Direction m_currentDirection = Idle;
	int jump = 0;
	int moveLeft = 0, moveRight = 0;
	bool stopFall = false;
private:
	std::string id = "Control";
	

};

