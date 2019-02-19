#include "MacroCommand.h"

MacroCommand::MacroCommand()
{

}

MacroCommand::~MacroCommand()
{
	std::cout << "deconstructing" << std::endl;
}

void MacroCommand::add(Command* command)
{
	commands.push_back(command);
	undoneCommands.clear();
}

void MacroCommand::remove(Command* command)
{
	commands.remove(command);
}


void MacroCommand::execute()
{
	std::cout << "executed" << std::endl;
}

void MacroCommand::undo()
{

	if (commands.size() > 0)
	{
		(*commands.rbegin())->undo();
		undoneCommands.push_back(*commands.rbegin());
		commands.pop_back();
	}

}

void MacroCommand::redo()
{
	if (undoneCommands.size() > 0)
	{
		(*undoneCommands.rbegin())->redo();
		commands.push_back(*undoneCommands.rbegin());
		undoneCommands.pop_back();
	}
}