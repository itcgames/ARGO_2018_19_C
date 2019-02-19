#pragma once
#include <iostream>
#include <string>

class Command
{
public: 
	virtual ~Command() {};
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;
	static void test() { std::cout << "Test" << std::endl; };
	static void testI(int t) { std::cout << "Test: "<< std::to_string(t) << std::endl; };

protected:
	Command() {};
};
