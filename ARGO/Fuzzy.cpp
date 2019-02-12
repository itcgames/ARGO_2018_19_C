#include "Fuzzy.h"



Fuzzy::Fuzzy()
{
}


Fuzzy::~Fuzzy()
{
}

double Fuzzy::fuzzyGrade(double value, double x0, double x1) {
	double result = 0;
	double x = value;

	if (x <= x0) {
		result = 0;
	}
	else if (x > x1) {
		result = 1;
	}
	else {
		result = ((x - x0) / (x1 - x0));
	}	
	return result;
}

double Fuzzy::fuzzyTriangle(double value, double x0, double x1, double x2)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x2)) {
		result = 0;
	}
	else if (x == x1) {
		result = 1;
	}
	else if ((x > x0) && (x < x1)) {
		result = ((x - x0) / (x1 - x0));
	}
	else {
		result = ((x2 - x) / (x2 - x1));
	}
	return result;
}

double Fuzzy::fuzzyTrape(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = value;
	
	if ((x <= x0) || (x >= x3)) {
		result = 0;
	}
	else if ((x >= x1) && (x <= x2)) {
		result = 1;
	}
	else if ((x > x0) && (x < x1)) {
		result = ((x - x0) / (x1 - x0));
	}
	else {
		result = ((x3 - x) / (x3 - x2));
	}
	return result;
}

double Fuzzy::fuzzyAnd(double A, double B)
{
	if (A > B) {
		return B;
	}
	return A;
}

double Fuzzy::fuzzyOr(double A, double B)
{
	if (A > B) {
		return A;
	}
	return B;
}

double Fuzzy::fuzzyNot(double A)
{
	return 1.0 - A;
}

void Fuzzy::update(double dis)
{
	//emeny threat is 22
	m_tiny = fuzzyTriangle(6, -10, 0, 10);
	m_small = fuzzyTrape(6, 2.5, 10, 15, 20);
	m_moderate = fuzzyTrape(6, 15, 20, 25, 30);
	m_large = fuzzyGrade(6, 25, 30);

	//put in values 250 == dis between ships
	m_close = fuzzyTriangle(dis, -300, 0, 300);
	m_medium = fuzzyTrape(dis, 200, 300, 500, 700);
	m_far = fuzzyGrade(dis, 500, 700);

	//this only returns high threat
	m_low = fuzzyOr(fuzzyAnd(m_medium, m_tiny), fuzzyAnd(m_medium, m_small));
	m_med = fuzzyAnd(m_close, m_tiny);
	m_high = fuzzyAnd(m_close, fuzzyNot(m_medium));

	//close
	if (m_low > m_med && m_low > m_high) {
		//std::cout << "threat low" << std::endl;
		//m_defuzz = 0;
	}
	//med
	if (m_med > m_low && m_med > m_high) {
		//std::cout << "threat med" << std::endl;
		//m_defuzz = 4;
	}
	//far
	if (m_high > m_low && m_high > m_med) {
		//std::cout << "threat high" << std::endl;
		//m_defuzz = 7;
	}

	//to make the player catchable then change 7 to lessser number

	//defuzzifaction
	m_defuzz = (m_low * 0 + m_high * 7) ;


}
double Fuzzy::runAway()
{
	return m_defuzz;
}


