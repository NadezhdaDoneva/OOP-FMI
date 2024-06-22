// BankingSystem.cpp  : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "Client.h"
#include "Application.h"
#include "CommandRun.h"


//class CommandFactory
//{
//public:
//    virtual Command* getCommand() = 0;
//    virtual MyString getCommandsDescription() const = 0;
//};
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
//class ClientSessionCommandFactory : public CommandFactory
//{
//
//};
//
//class Session
//{
//public:
//    Session(CommandFactory* commandFactory) : commandFactory(commandFactory) {}
//    virtual void printMenu() = 0;
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

int main()
{
    /*while (1)
    {
        Session s(new NanSessionCommandFactory());
        s.handle();
    }*/
   /* Client cl = Client("Ivan", "12", 23, "12");
    cl.whoami();*/
    Application* bankApp = &Application::getInstance();
    RunCommand runC;
    while (true) {
        runC.execute(bankApp);
    }
}


