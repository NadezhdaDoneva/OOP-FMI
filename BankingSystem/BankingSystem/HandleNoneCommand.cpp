#include "HandleNoneCommand.h"
#include "CommandRegister.h"
#include "CommandLogin.h"

void HandleNoneCommand::execute(Application* app) {
	RegisterCommand rc;
	LoginCommand lc;

	int n = 0;
	std::cout << "Choose: \n 1) Register\n 2) Login\n 3) Exit\n";
	std::cin >> n;

	switch (n)
	{
	case 1: rc.execute(app); break;
	case 2: lc.execute(app); break;
	case 3: break; //app->logout(); break;
	default: std::cout << "Unknown command!\n"; break;
	}
}
