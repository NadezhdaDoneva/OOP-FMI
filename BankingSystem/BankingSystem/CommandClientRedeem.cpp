#include "CommandClientRedeem.h"

int RedeemCommand::execute() {
	MyString bankName, verificationCode;
	unsigned accountNumber;
	std::cin >> bankName >> accountNumber >> verificationCode;
	try {
		User* curClient = app->getLogedUser();
		if (Client* cur = dynamic_cast<Client*>(curClient))
			cur->redeem(bankName, accountNumber, verificationCode);
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
