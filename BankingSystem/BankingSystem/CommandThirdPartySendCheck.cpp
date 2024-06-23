#include "CommandThirdPartySendCheck.h"

int SendCheckCommand::execute() {
	double sum;
	MyString verificationCode, egn;
	std::cin >> sum >> verificationCode >> egn;
	try {
		app->sendCheck(sum, verificationCode, egn);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
    return 3;
}
