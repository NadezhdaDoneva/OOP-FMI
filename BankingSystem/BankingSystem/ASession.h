#pragma once
#include "ACommadFactory.h"
#include "ACommandFactoryFactory.h"

class Session
{

public:
    Session(CommandFactory* commandFactory) : commandFactory(commandFactory) {} //clone
    void handle()
    {
        std::cout << commandFactory->getCommandsDescription() << std::endl;

        while (true)
        {
            Command* current = commandFactory->getCommand();
            if (!current)
            {
                break;
            }
            int code = current->execute();
            commandFactory = CommandFactoryFactory(code); 
            std::cout << commandFactory->getCommandsDescription();
            delete current;
        }
    }
    CommandFactory* commandFactory;
};