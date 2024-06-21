#include "Application.h"
#include <fstream>

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

void Application::open(const MyString& bankName) {
	unsigned idx = getIdxOfBankByName(bankName);
	Task task("Open", logged->getUsername(), bankName);
	banks[idx].assignTask(task);
}

void Application::close(const MyString& bankName, unsigned accountNumber) {
	unsigned idx = getIdxOfBankByName(bankName);
	Task task("Close", logged->getUsername(), bankName, accountNumber);
	banks[idx].assignTask(task);
}

void Application::change(const MyString& newBankName, const MyString& curBankName, unsigned accountNumber) {
	unsigned idx = getIdxOfBankByName(curBankName);
	Task task("Change", logged->getUsername(), curBankName, accountNumber);
	banks[idx].assignTask(task);
}

//void Application::redeem(const MyString& bankName, unsigned accountNumber, const MyString& verificationCode) {
//	User* curClient = getLoggedUser();
//	if (Client* cur = dynamic_cast<Client*>(curClient)) {
//		if (cur->IdxOfBankWithThatAccountNum(bankName, accountNumber) != -1) {
//			int idx = cur->getIdxOfCheckByCode(verificationCode);
//			if (idx != -1) {
//
//			}
//			else {
//				throw std::runtime_error("Wrong code.");
//			}
//		}
//	}
//}


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

void Application::load() {
	//Load clients
	std::ifstream cif("clients.dat", std::ios::in | std::ios::binary);
	if (!cif.is_open())
		throw std::runtime_error("Can't open the file!");
	int clCount = 0;
	cif.read((char*)&clCount, sizeof clCount);
	for (int i = 0; i < clCount; i++)
	{
		Client cl;
		cl.readFromFile(cif);
		clientUsers.pushBack(std::move(cl));
	}
	cif.close();

	//Load thirdParties
	std::ifstream tif("clients.dat", std::ios::in | std::ios::binary);
	if (!tif.is_open())
		throw std::runtime_error("Can't open the file!");
	int ThirdPartyCount = 0;
	tif.read((char*)&ThirdPartyCount, sizeof ThirdPartyCount);
	for (int i = 0; i < ThirdPartyCount; i++)
	{
		ThirdParty tr;
		tr.readFromFile(tif);
		thirdPartyUsers.pushBack(std::move(tr));
	}
	tif.close();

	//Load checks
	/*std::ifstream chif("clients.dat", std::ios::in | std::ios::binary);
	if (!chif.is_open())
		throw std::runtime_error("Can't open the file!");
	int checksCount = 0;
	chif.read((char*)&checksCount, sizeof checksCount);
	for (int i = 0; i < checksCount; i++)
	{
		Check ch;
		ch.readFromFile(chif);
		checks.pushBack(std::move(ch));
	}
	chif.close();*/

	//Load Banks
	std::ifstream bif("banks.dat", std::ios::out | std::ios::binary);
	if (!bif.is_open())
		throw std::runtime_error("Can't open the file!");
	int banksCount = 0;
	bif.read((char*)&banksCount, sizeof banksCount);
	for (size_t i = 0; i < banksCount; i++) {
		Bank bank;
		bank.readFromFile(bif);
		banks.pushBack(std::move(bank));
	}
	bif.close();

	//Load session
	std::ifstream sif("session.dat", std::ios::in | std::ios::binary);
	if (!sif.is_open())
		throw std::exception("File not open.");

	MyString username = "";
	sif.read((char*)&username, sizeof username);
	LoggedUserType type;
	sif.read((char*)&type, sizeof type);

	if (type == LoggedUserType::client) {
		int clientsCount = clientUsers.getSize();
		for (int i = 0; i < clientsCount; i++) {
			if (clientUsers[i].getUsername() == username)
				logged = &clientUsers[i];
		}
	}
	else if (type == LoggedUserType::employee) {
		int banksCount = banks.getSize();
		for (int i = 0; i < banksCount; i++) {
			if (banks[i].searchEmployeeByUsername(username)) {
				logged = banks[i].searchEmployeeByUsername(username);
			}
		}
	}
	else if (type == LoggedUserType::thirdParty) {
		int thirdPartyCount = thirdPartyUsers.getSize();
		for (int i = 0; i < thirdPartyCount; i++)
		{
			if (thirdPartyUsers[i].getUsername() == username)
				logged = &thirdPartyUsers[i];
		}
	}
}

void Application::save() const {

	//Save session
	std::ofstream sof("session.dat", std::ios::out | std::ios::binary);
	if (!sof.is_open())
		throw std::runtime_error("Can't open the file!");

	MyString username = "";
	if (logged == nullptr) {
		username = "No logged user";
	}
	else {
		username = logged->getUsername();
	}
	sof.write((const char*)&username, sizeof username);
	sof.write((const char*)&type, sizeof type);
	sof.close();

	//Save clients
	std::ofstream cof("clients.dat", std::ios::out | std::ios::binary);
	if (!cof.is_open())
		throw std::runtime_error("Can't open the file!");
	int clCount = clientUsers.getSize();
	cof.write((const char*)&clCount, sizeof clCount);
	for (int i = 0; i < clCount; i++)
		clientUsers[i].saveToFile(cof);
	cof.close();

	//Save Banks
	std::ofstream bof("banks.dat", std::ios::out | std::ios::binary);
	if (!bof.is_open())
		throw std::runtime_error("Can't open the file!");
	int banksCount = banks.getSize();
	for (int i = 0; i < banksCount; i++) {
		banks[i].saveToFile(bof);
	}

	//Save thirdParties
	std::ofstream tof("thirdParty.dat", std::ios::out | std::ios::binary);
	if (!tof.is_open())
		throw std::runtime_error("Can't open the file!");
	int thirdPartyCount = thirdPartyUsers.getSize();
	tof.write((const char*)&thirdPartyCount, sizeof thirdPartyCount);
	for (int i = 0; i < thirdPartyCount; i++)
		thirdPartyUsers[i].saveToFile(tof);
	tof.close();

	//Save checks
	/*std::ofstream chof("checks.dat", std::ios::out | std::ios::binary);
	if (!chof.is_open())
		throw std::runtime_error("Can't open the file!");
	int checksCount = checks.getSize();
	chof.write((const char*)&checksCount, sizeof checksCount);
	for (int i = 0; i < checksCount; i++)
		checks[i].saveToFile(chof);
	chof.close();*/
}
