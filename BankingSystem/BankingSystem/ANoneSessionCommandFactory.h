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
        case 1: return new RegisterCommand(); break;
        case 2: return new LoginCommand(); break;
        case 3: return new CreateBankCommand(); break;
        case 4: return nullptr; break;
        default: std::cout << "Unknown command!\n"; break;
        }
    }
    MyString getCommandsDescription() const
    {
        return "\nChoose: \n 1) Register\n 2) Login\n 3) Create bank\n 4) Exit\n";
    }
};