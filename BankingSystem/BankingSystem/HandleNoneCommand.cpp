#include "HandleNoneCommand.h"
#include "CommandRegister.h"
#include "CommandLogin.h"
#include "CommandCreateBank.h"

void HandleNoneCommand::execute(Application* app) {
	RegisterCommand rc;
	LoginCommand lc;
	CreateBankCommand cc;

	int n = 0;
	std::cout << "Choose: \n 1) Register\n 2) Login\n 3) Create bank\n 4) Exit\n";
	std::cin >> n;

	switch (n)
	{
	case 1: rc.execute(app); break;
	case 2: lc.execute(app); break;
	case 3: cc.execute(app); break;
	case 4: break; //app->logout(); break;
	default: std::cout << "Unknown command!\n"; break;
	}
}
