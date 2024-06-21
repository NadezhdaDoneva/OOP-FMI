#include "CommandClientOpen.h"

void OpenCommand::execute(Application* app) {
	MyString bankName;
	std::cin >> bankName;
	try {
		app->open(bankName);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}
