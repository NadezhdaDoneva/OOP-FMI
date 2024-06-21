#include "CommandRegister.h"
#include "CommandRegisterClient.h"
#include "CommandRegisterEmployee.h"
#include "CommandRegisterThirdParty.h"

void RegisterCommand::execute(Application* app) {
	RegClientCommand rcc;
	RegEmployeeCommand rec;
	RegThirdPartyCommand rtc;

	int n = 0;
	std::cout << "Choose: \n 1 - Client, \n 2 - Employee, \n 3 - Third Party \n";
	std::cin >> n;
	switch (n)
	{
	case 1: rcc.execute(app);
		break;
	case 2: rec.execute(app);
		break;
	case 3: rtc.execute(app);
	default:
		std::cout << "Unknown command\n";
		break;
	}
}
