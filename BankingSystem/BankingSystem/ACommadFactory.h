#pragma once
#include "Command.h"

class CommandFactory
{
public:
    virtual Command* getCommand() = 0;
    virtual MyString getCommandsDescription() const = 0;
    virtual ~CommandFactory() = default;
};