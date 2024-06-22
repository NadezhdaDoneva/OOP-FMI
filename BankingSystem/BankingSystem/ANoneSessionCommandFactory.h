#pragma once
#include "Command.h"
#include "ACommadFactory.h"
#include "CommandRegister.h"
#include "CommandLogin.h"
#include "CommandCreateBank.h"

class NanSessionCommandFactory : public CommandFactory
{
    Command* getCommand() override
    {

        int n = 0;
        std::cin >> n;

        switch (n)
        {
        case 1: return new RegisterCommand();
        case 2: return new LoginCommand();
        case 3: return new CreateBankCommand();
        case 4: return nullptr;
        default: std::cout << "Unknown command!\n"; break;
        }
    }
    MyString getCommandsDescription() const
    {
        return "Choose: \n 1) Register\n 2) Login\n 3) Create bank\n 4) Exit\n";
    }
};