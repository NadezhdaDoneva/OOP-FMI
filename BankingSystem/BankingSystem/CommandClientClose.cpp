#include "CommandClientClose.h"

int CloseCommand::execute() {
	MyString bankName;
	unsigned accountNumber;
	std::cin >> bankName >> accountNumber;

	try {
		app->closeCl(bankName, accountNumber);
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
