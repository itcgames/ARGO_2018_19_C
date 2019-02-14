#pragma once
#include "Animation.h"
#include "SDL.h"

class State
{
public:
	virtual void idle(AnimationComponent* a)
	{
	//	std::cout << "State::Idling" << std::endl;
	}

	virtual void jumpLeft(AnimationComponent* a)
	{
		//std::cout << "State::leftJump" << std::endl;
	}

	virtual void jumpRight(AnimationComponent* a)
	{
		//std::cout << "State::rightJump" << std::endl;
	}

	virtual void right(AnimationComponent* a)
	{
		//std::cout << "State::Right" << std::endl;
	}

	virtual void left(AnimationComponent* a)
	{
		//std::cout << "State::Left" << std::endl;
	}

	virtual void die(AnimationComponent* a)
	{
		std::cout << "State::Die" << std::endl;
	}

};