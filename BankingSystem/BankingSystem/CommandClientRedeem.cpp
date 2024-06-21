#include "CommandClientRedeem.h"

void RedeemCommand::execute(Application* app) {
	MyString bankName, verificationCode;
	unsigned accountNumber;
	std::cin >> bankName >> accountNumber >> verificationCode;
	try {
		User* curClient = app->getLoggedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient))
			cur->redeem(bankName, accountNumber, verificationCode);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}