#include "Application.h"

Application& Application::getInstance() {
	static Application app;
	return app;
}

const DynamicArray<Bank>& Application::getBanks() const
{
	return this->banks;
}

void Application::registerClient(Client&& client) {
	if (doesUserAlreadyExist(std::move(client))) {
		throw std::runtime_error("User already exists");
	}
	else {
		clientUsers.pushBack(std::move(client));
	}
}

void Application::registerEmployee(Employee&& employee, const MyString& bankName) {
	if (doesUserAlreadyExist(std::move(employee))) {
		throw std::runtime_error("User already exists");
	}
	else {
		int idxOfBank = getIdxOfBankByName(bankName);
		banks[idxOfBank].addEmployee(employee);
	}
}

void Application::registerThirdParty(ThirdParty&& thirdParty) {
	if (doesUserAlreadyExist(std::move(thirdParty))) {
		throw std::runtime_error("User already exists");
	}
	else {
		thirdPartyUsers.pushBack(std::move(thirdParty));
	}
}

void Application::login(const MyString& username, const MyString& password) {
	int banksCount = banks.getSize();

	//search for employee with the same username and pass in each bank 
	for (int i = 0; i < banksCount; i++) {
		DynamicArray<Employee> employeesInCurBank = banks[i].getEmployees();
		int employeesInCurBankCount = employeesInCurBank.getSize();

		for (int j = 0; j < employeesInCurBankCount; j++) {
			if (employeesInCurBank[j].getUsername() == username && employeesInCurBank[j].isValidPassword(password)) {
				logged = &employeesInCurBank[j];
				type = LoggedUserType::employee;
				return;
			}
			else {
				throw std::runtime_error("wrong username or pass");
			}
		}
	}

	//search for a client with that username and pass
	int clientUsersCount = clientUsers.getSize();
	for (int i = 0; i < clientUsersCount; i++) {
		if (clientUsers[i].getUsername() == username && clientUsers[i].isValidPassword(password)) {
			logged = &clientUsers[i];
			type = LoggedUserType::client;
			return;
		}
		else {
			throw std::runtime_error("wrong username or pass");
		}
	}

	//search for a thirdParty with that username and pass
	int thirdPartyUsersCount = thirdPartyUsers.getSize();
	for (int i = 0; i < thirdPartyUsersCount; i++) {
		if (thirdPartyUsers[i].getUsername() == username && thirdPartyUsers[i].isValidPassword(password)) {
			logged = &thirdPartyUsers[i];
			type = LoggedUserType::thirdParty;
			return;
		}
		else {
			throw std::runtime_error("wrong username or pass");
		}
	}
}

void Application::login(MyString&& username, MyString&& password) {
	int banksCount = banks.getSize();

	//search for employee with the same username and pass in each bank 
	for (int i = 0; i < banksCount; i++) {
		DynamicArray<Employee> employeesInCurBank = banks[i].getEmployees();
		int employeesInCurBankCount = employeesInCurBank.getSize();

		for (int j = 0; j < employeesInCurBankCount; j++) {
			if (employeesInCurBank[j].getUsername() == username && employeesInCurBank[j].isValidPassword(password)) {
				logged = &employeesInCurBank[j];
				type = LoggedUserType::employee;
				return;
			}
			else {
				throw std::runtime_error("wrong username or pass");
			}
		}
	}

	//search for a client with that username and pass
	int clientUsersCount = clientUsers.getSize();
	for (int i = 0; i < clientUsersCount; i++) {
		if (clientUsers[i].getUsername() == username && clientUsers[i].isValidPassword(password)) {
			logged = &clientUsers[i];
			type = LoggedUserType::client;
			return;
		}
		else {
			throw std::runtime_error("wrong username or pass");
		}
	}

	//search for a thirdParty with that username and pass
	int thirdPartyUsersCount = thirdPartyUsers.getSize();
	for (int i = 0; i < thirdPartyUsersCount; i++) {
		if (thirdPartyUsers[i].getUsername() == username && thirdPartyUsers[i].isValidPassword(password)) {
			logged = &thirdPartyUsers[i];
			type = LoggedUserType::thirdParty;
			return;
		}
		else {
			throw std::runtime_error("wrong username or pass");
		}
	}
}

void Application::logout() {
	logged = nullptr;
	type = LoggedUserType::none;
}

void Application::whoami() {
	User* curUser = getLoggedUser();
	if (curUser != nullptr) {
		std::cout << "You are " << curUser->getUsername();
	}
}

void Application::help() {
	if (type == LoggedUserType::client) {
		std::cout << "Client help menu: ";
	}
	else if (type == LoggedUserType::employee) {
		std::cout << "Employee help menu: ";
	}
	else if (type == LoggedUserType::thirdParty) {
		std::cout << "Third party help menu: ";
	}
}



const User* Application::getLoggedUser() const
{
	return logged;
}

User* Application::getLoggedUser()
{
	return logged;
}

LoggedUserType Application::getType() const
{
	return type;
}

bool Application::doesUserAlreadyExist(User&& user) const {
	int banksCount = banks.getSize();

	//search for employee with the same username in each bank 
	for (int i = 0; i < banksCount; i++) {
		DynamicArray<Employee> employeesInCurBank = banks[i].getEmployees();
		int employeesInCurBankCount = employeesInCurBank.getSize();

		for (int j = 0; j < employeesInCurBankCount; j++) {
			if (employeesInCurBank[j].getUsername() == user.getUsername()) {
				return true;
			}
		}
	}

	//check for a client with the same uername
	int clientUsersCount = clientUsers.getSize();
	for (int i = 0; i < clientUsersCount; i++) {
		if (clientUsers[i].getUsername() == user.getUsername()) {
			return true;
		}
	}

	//check for a thirdParty with the same username
	int thirdPartyUsersCount = thirdPartyUsers.getSize();
	for (int i = 0; i < thirdPartyUsersCount; i++) {
		if (thirdPartyUsers[i].getUsername() == user.getUsername()) {
			return true;
		}
	}

	return false;
}

int Application::getIdxOfBankByName(const MyString& bankName) const {
	int countOfBanks = banks.getSize();
	if (countOfBanks == 0) {
		throw std::runtime_error("There are no existing banks.");
	}

	for (size_t i = 0; i < countOfBanks; i++) {
		if (banks[i].getBankName() == bankName) {
			return i;
		}
	}

	throw std::runtime_error("No bank with such name.");
}

void Application::createBank(const MyString& bankName) {
	//check if there is an existing bank with the same name
	int countOfBanks = banks.getSize();
	for (size_t i = 0; i < countOfBanks; i++) {
		if (banks[i].getBankName() == bankName) {
			throw std::runtime_error("A bank with the same name already exists.");
		}
	}

	Bank newBank(bankName);
	banks.pushBack(newBank);
}


void Application::addClient(const Client& client) {
    clientUsers.pushBack(client);
}

void Application::addClient(Client&& client){
    clientUsers.pushBack(std::move(client));
}

void Application::addThirdParty(const ThirdParty& thirdParty) {
	thirdPartyUsers.pushBack(thirdParty);
}

void Application::addThirdParty(ThirdParty&& thirdParty) {
	thirdPartyUsers.pushBack(std::move(thirdParty));
}
