// BankingSystem.cpp  : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ASession.h"
#include "ANoneSessionCommandFactory.h"

void runBankingSystem() {
        Session s(new NanSessionCommandFactory());
        s.handle();
}

int main() {
    runBankingSystem();
}


