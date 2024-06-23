#include "CommandClientRedeem.h"

int RedeemCommand::execute() {
	MyString bankName, verificationCode;
	unsigned accountNumber;
	std::cin >> bankName >> accountNumber >> verificationCode;
	try {
	    app->redeem(bankName, accountNumber, verificationCode);
		std::cout << "You successfully redeemed the check" << std::endl;
		return 1;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
