// BankingSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Client.h"

int main()
{
    Client cl = Client("Ivan", "12", 23, "12");
    cl.whoami();
}

