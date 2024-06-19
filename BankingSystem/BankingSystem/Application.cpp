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
		
	}
}

void Application::registerEmployee(Employee&& employee) {
	if (doesUserAlreadyExist(std::move(employee))) {
		throw std::runtime_error("User already exists");
	}
	else {
		//TO DO
	}
}

void Application::registerThirdParty(ThirdParty&& thirdParty) {
	if (doesUserAlreadyExist(std::move(thirdParty))) {
		throw std::runtime_error("User already exists");
	}
	else {
		//TO DO
	}
}

void Application::login(const MyString& username, const MyString& password)
{
}

void Application::login(MyString&& username, MyString&& password)
{
}

void Application::logout()
{
}

const User* Application::getLoggedUser() const
{
	return nullptr;
}

User* Application::getLoggedUser()
{
	return nullptr;
}

LoggedUserType Application::getType() const
{
	return LoggedUserType();
}

bool Application::doesUserAlreadyExist(User&& user) const {
	int banksCount = banks.getSize();

	//search for a user with the same username in every bank //this checks if there is no employee or client with the same username 
	for (int i = 0; i < banksCount; i++) {

		DynamicArray<Client> clientsInCurBank = banks[i].getClients();
		int clientsInCurBankCount = clientsInCurBank.getSize();

		for (int j = 0; j < clientsInCurBankCount; j++) {
			if (clientsInCurBank[j].getUsername() == user.getUsername()) {
				return true;
			}
		}

		DynamicArray<Employee> employeesInCurBank = banks[i].getEmployees();
		int employeesInCurBankCount = employeesInCurBank.getSize();

		for (int j = 0; j < employeesInCurBankCount; j++) {
			if (employeesInCurBank[j].getUsername() == user.getUsername()) {
				return true;
			}
		}
	}

	//check for a thirdParty with the same username
	int thirdPartyUsersCount = thirdPartyUsers.getSize();
	for (int j = 0; j < thirdPartyUsersCount; j++) {
		if (thirdPartyUsers[j].getUsername() == user.getUsername()) {
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
