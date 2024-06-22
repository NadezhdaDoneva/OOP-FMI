#include "CommandCreateBank.h"

void CreateBankCommand::execute(Application* app) {
	MyString bankName;
	std::cout << "Input bank name:";
	std::cin >> bankName;
	try {
		app->createBank(bankName);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
