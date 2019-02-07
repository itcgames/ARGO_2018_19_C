#pragma once
#include <iostream>
#include "Component.h"
#include <SDL.h>

class AnimationComponent : public Component
{
	
	class State* m_current;

public:
	AnimationComponent();
	void setCurrent(State* s);
	State* getCurrent();

	void idle();

	void leftJump();

	void rightJump();

	void right();

	void left();

	std::string getID()
	{
		return id;
	}

	std::string id = "Animation";
};


