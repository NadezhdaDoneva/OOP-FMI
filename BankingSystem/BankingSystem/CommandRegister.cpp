#include "CommandRegister.h"
#include "CommandRegisterClient.h"
#include "CommandRegisterEmployee.h"
#include "CommandRegisterThirdParty.h"

int RegisterCommand::execute() {
	RegClientCommand rcc;
	RegEmployeeCommand rec;
	RegThirdPartyCommand rtc;

	int n = 0;
	std::cout << "Choose: \n 1 - Client, \n 2 - Employee, \n 3 - Third Party \n";
	std::cin >> n;
	switch (n)
	{
	case 1: rcc.execute();
		break;
	case 2: rec.execute();
		break;
	case 3: rtc.execute();
	default:
		std::cout << "Unknown command\n";
		break;
	}
	return 0;
}
