// BankingSystem.cpp  : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "Client.h"
#include "Application.h"
#include "CommandRun.h"
#include "ASession.h"
#include "ANoneSessionCommandFactory.h"

//
//class CommandFactory
//{
//public:
//    virtual Command* getCommand() = 0;
//    virtual MyString getCommandsDescription() const = 0;
//};
//
//class NanSessionCommandFactory : public CommandFactory
//{
//    Command* getCommand() override
//    {
//
//        int n = 0;   
//        std::cin >> n;
//
//        switch (n)
//        {
//        case 1: return new RegisterCommand();
//        case 2: return new LoginCommand();
//        case 3: return new CreateBankCommand();
//        case 4: return nullptr;
//        default: std::cout << "Unknown command!\n"; break;
//        }
//    }
//    MyString getCommandsDescription() const
//    {
//        return "Choose: \n 1) Register\n 2) Login\n 3) Create bank\n 4) Exit\n";
//    }
//};
//
//class ClientSessionCommandFactory : public CommandFactory {
//public:
//    Command* getCommand() override
//    {
//
//        int n = 0;
//        std::cin >> n;
//
//        switch (n)
//        {
//        case 1: return new RegisterCommand();
//        case 2: return new LoginCommand();
//        case 3: return new CreateBankCommand();
//        case 4: return nullptr;
//        default: std::cout << "Unknown command!\n"; break;
//        }
//    }
//    MyString getCommandsDescription() const
//    {
//        return "Choose: \n 1) Register\n 2) Login\n 3) Create bank\n 4) Exit\n";
//    }
//
//};
//
//class ClientSessionCommandFactory : public CommandFactory
//{
//    Command* getCommand() override {
//        int n;
//        std::cin >> n;
//
//        switch (n)
//        {
//        case 1:
//            return new OpenCommand(); break;
//        case 2:
//            return new CloseCommand(); break;
//        case 3:
//            return new CheckAvailableCommand(); break;
//        case 4:
//            return new ChangeCommand(); break;
//        case 5:
//            return new ListCommand(); break;
//        case 6:
//            return new MessagesCommand(); break;
//        case 7:
//            return new RedeemCommand(); break;
//        case 8:
//            app->logout(); break;
//        case 9:
//            break;
//        default:
//            std::cout << "Unknown command!\n"; break;
//        }
//    }
//
//    MyString getCommandsDescription() const
//    {
//        std::cout << "Choose: \n 1) open\n 2) close\n 3) check available\n 4) change\n 5) list\n 6) messages\n 7) redeem\n 8) logout 9) exit";
//    }
//};
//
//class Session
//{
//public:
//    Session(CommandFactory* commandFactory) : commandFactory(commandFactory) {}
//    void handle()
//    {
//        std::cout << commandFactory->getCommandsDescription() << std::endl;
//
//        while (true)
//        {
//            Command* current = commandFactory->getCommand();
//            if (!current)
//            {
//                break;
//            }
//            current->execute(&Application::getInstance());
//            delete current;
//        }
//    }
//    CommandFactory* commandFactory;
//};


void runBankingSystem()
{
    while (1)
    {
        Session s(new NanSessionCommandFactory());
        s.handle();
    }
}
int main()
{
    runBankingSystem();

   /* Client cl = Client("Ivan", "12", 23, "12");
    cl.whoami();*/
    /*Application* bankApp = &Application::getInstance();
    RunCommand runC;
    while (true) {
        runC.execute(bankApp);
    }*/
}


