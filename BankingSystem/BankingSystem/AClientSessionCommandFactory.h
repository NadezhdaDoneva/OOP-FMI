#pragma once
#include "ACommadFactory.h"
#include "CommandClientChange.h"
#include "CommandClientCheckAvailable.h"
#include "CommandClientClose.h"
#include "CommandClientList.h"
#include "CommandClientMessages.h"
#include "CommandClientOpen.h"
#include "CommandClientRedeem.h"
#include "CommandLogout.h"


class ClientSessionCommandFactory : public CommandFactory
{
    Command* getCommand() override {
        int n;
        std::cin >> n;

        switch (n)
        {
        case 1:
            return new OpenCommand(); break;
        case 2:
            return new CloseCommand(); break;
        case 3:
            return new CheckAvailableCommand(); break;
        case 4:
            return new ChangeCommand(); break;
        case 5:
            return new ListCommand(); break;
        case 6:
            return new MessagesCommand(); break;
        case 7:
            return new RedeemCommand(); break;
        case 8:
            return new LogoutCommand(); break;
        case 9:
            break;
        default:
            std::cout << "Unknown command!\n"; break;
        }
    }

    MyString getCommandsDescription() const
    {
       return "Choose: \n 1) open\n 2) close\n 3) check available\n 4) change\n 5) list\n 6) messages\n 7) redeem\n 8) logout\n 9) exit\n";
    }
};