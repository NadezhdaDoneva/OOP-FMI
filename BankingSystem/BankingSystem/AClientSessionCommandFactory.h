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
#include "CommandWhoAmI.h"
#include "CommandHelp.h"


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
            return new WhoAmICommand(); break;
        case 9:
            return new HelpCommand(); break;
        case 10:
            return new LogoutCommand(); break;
        default:
            std::cout << "Unknown command!\n"; break;
        }
    }

    MyString getCommandsDescription() const
    {
       return "Choose: \n 1) open [bankname]\n 2) close [bankname, accNum]\n 3) check available [bankname, accNum]\n 4) change [newBankName, curBankName, accNum]\n 5) list [bankName]\n 6) messages\n 7) redeem [bankName, accNum, verCode]\n 8) whoami\n 9) help\n 10) logout\n";
    }
};