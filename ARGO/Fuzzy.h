#pragma once
//#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Fuzzy
{
public:
	Fuzzy();
	~Fuzzy();
	void update(double dis);
	double m_close = 0;
	double m_medium = 0;
	double m_far = 0;

	double m_tiny = 0;
	double m_small= 0;
	double m_moderate = 0;
	double m_large = 0;

	double m_low = 0;
	double m_med = 0;
	double m_high = 0;

	double m_threat = 0;
	double m_run = 0;
	double m_defuzz = 0;
	double runAway();

private:
	double fuzzyGrade(double value, double x0, double x1);
	double fuzzyTriangle(double value, double x0, double x1, double x2);
	double fuzzyTrape(double value, double x0, double x1, double x2, double x3);
	double fuzzyAnd(double A, double B);
	double fuzzyOr(double A, double B);
	double fuzzyNot(double A);

};

