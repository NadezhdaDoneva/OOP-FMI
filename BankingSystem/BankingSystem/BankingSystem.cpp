// BankingSystem.cpp  : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "Client.h"
#include "Application.h"
#include "ASession.h"
#include "ANoneSessionCommandFactory.h"

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
}


