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

	void die();

	std::string getID()
	{
		return id;
	}

	std::string id = "Animation";


	SDL_Rect sRect = {80,0,80,100};

	enum AniState {
		idleS,
		leftS,
		rightS,
		jumpLeftS,
		jumpRightS,
		DieS
	};

	AniState getCurrentState();

	void setCurrentState(AniState a);

	AniState m_currentState = idleS;

	float m_scale = 1;
	
};


