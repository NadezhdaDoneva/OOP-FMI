#include "CommandClientOpen.h"

int OpenCommand::execute() {
	MyString bankName;
	std::cout << "Input bankname: ";
	std::cin >> bankName;
	try {
		app->openCl(bankName);
		std::cout << "Successfully requested opening an account.";
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
