#include "CommandCreateBank.h"

int CreateBankCommand::execute() {
	MyString bankName;
	std::cout << "Input bank name:";
	std::cin >> bankName;
	try {
		app->createBank(bankName);
		std::cout << "Bank created.\n";
		return 0;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
