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
