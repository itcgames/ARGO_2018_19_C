#pragma once
#include "Component.h"
class ScoreComponent : public Component
{

public:
	ScoreComponent(float score) : m_score(score){};

	
	float getScore() {
		return m_score;
	}

	void setScore(float score) {
		this->m_score = score;
	}
	std::string getID()
	{
		return id;
	}

private:
	float m_score;
	std::string  id = "Score";
};