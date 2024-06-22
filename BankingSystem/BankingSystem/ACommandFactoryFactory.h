#pragma once
#include "ANoneSessionCommandFactory.h"
#include "AClientSessionCommandFactory.h"
#include "AEmployeeSessionCommandFactory.h"
#include "AThirdPartySessionCommandFactory.h"

CommandFactory* CommandFactoryFactory(int code)
{
    switch (code)
    {
    case 0: return new NanSessionCommandFactory(); break;
    case 1: return new ClientSessionCommandFactory(); break;
    case 2: return new EmployeeSessionCommandFactory(); break;
    case 3: return new ThirdPartySessionCommandFactory(); break;
    }
}
