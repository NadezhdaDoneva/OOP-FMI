#include "Application.h"
#include <fstream>

Application& Application::getInstance() {
	static Application app;
	return app;
}

const DynamicArray<Bank>& Application::getBanks() const {
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
				logged = &banks[i].getEmployees()[j];
				//logged = &employeesInCurBank[j];
				type = LoggedUserType::employee;
				return;
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
	}

	//search for a thirdParty with that username and pass
	int thirdPartyUsersCount = thirdPartyUsers.getSize();
	for (int i = 0; i < thirdPartyUsersCount; i++) {
		if (thirdPartyUsers[i].getUsername() == username && thirdPartyUsers[i].isValidPassword(password)) {
			logged = &thirdPartyUsers[i];
			type = LoggedUserType::thirdParty;
			return;
		}
	}
	throw std::runtime_error("wrong username or pass");
}

void Application::logout() {
	logged = nullptr;
	type = LoggedUserType::none;
}

void Application::whoami() {
	User* curUser = getLogedUser();
	if (curUser != nullptr) {
		std::cout << "You are " << curUser->getUsername() << std::endl;
	}
}

void Application::help() {
	if (type == LoggedUserType::client) {
		std::cout << "Client help menu: ... " << std::endl;
	}
	else if (type == LoggedUserType::employee) {
		std::cout << "Employee help menu: ..." << std::endl;
	}
	else if (type == LoggedUserType::thirdParty) {
		std::cout << "Third party help menu: ..." << std::endl;
	}
}

User* Application::getLogedUser() {
	return logged;
}

const User* Application::getLoggedUser() const {
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
	int countOfBanks = banks.getSize();
	for (size_t i = 0; i < countOfBanks; i++) {
		if (banks[i].getBankName() == bankName) {
			throw std::runtime_error("A bank with the same name already exists.");
		}
	}

	Bank newBank(bankName);
	banks.pushBack(newBank);
}

void Application::openCl(const MyString& bankName) {
	unsigned idx = getIdxOfBankByName(bankName);
	Task task("Open", logged->getUsername(), bankName);
	banks[idx].assignTask(task);
}

void Application::closeCl(const MyString& bankName, unsigned accountNumber) {
	unsigned idx = getIdxOfBankByName(bankName);
	Task task("Close", logged->getUsername(), bankName, accountNumber);
	banks[idx].assignTask(task);
}

void Application::changeCl(const MyString& newBankName, const MyString& curBankName, unsigned accountNumber) {
	unsigned idx = getIdxOfBankByName(curBankName);
	Task task("Change", logged->getUsername(), curBankName, accountNumber);
	banks[idx].assignTask(task);
}

double Application::checkAvailable(const MyString& bankName, unsigned accountNumber) {
	int idx = getIdxOfBankByName(bankName);
	double balance = banks[idx].getBalanceByAccountNumber(accountNumber);
	return balance;
}

void Application::openEmpl(const MyString& username, const MyString& bankName) {
	int idxB = getIdxOfBankByName(bankName);
	MyString newMess = banks[idxB].openAccount(username);
	int idxCl = getIdxOfClientByName(username);
	clientUsers[idxCl].sendMessage(newMess);
}

void Application::closeEmpl(const MyString& username, const MyString& bankName, unsigned accountNumber) {
	int idxB = getIdxOfBankByName(bankName);
	MyString newMess = banks[idxB].closeAccount(username, accountNumber);
	int idxCl = getIdxOfClientByName(username);
	clientUsers[idxCl].sendMessage(newMess);
}

void Application::changeEmpl(const MyString& username, const MyString& newBankName, const MyString& curBankName, unsigned accountNumber) {
	int idxCurBank = getIdxOfBankByName(curBankName);
	int idxNewBank = getIdxOfBankByName(newBankName);
	MyString curBankMess = banks[idxCurBank].removeBankAcc(username, curBankName, accountNumber);
	MyString newBankMess = banks[idxCurBank].addBankAcc(username, newBankName);
	int idxCl = getIdxOfClientByName(username);
	clientUsers[idxCl].sendMessage(curBankMess);
	clientUsers[idxCl].sendMessage(newBankMess);
}

int Application::getIdxOfClientByName(const MyString& username) const {
	int clientsCount = clientUsers.getSize();
	for (int i = 0; i < clientsCount; i++) {
		if (clientUsers[i].getUsername() == username)
			return i;
	}
	throw std::runtime_error("there is no client with that username.");
}

int Application::getIdxOfClientByEgn(const MyString& egn) const {
	int clientsCount = clientUsers.getSize();
	for (int i = 0; i < clientsCount; i++) {
		if (clientUsers[i].getEGN() == egn)
			return i;
	}
	throw std::runtime_error("there is no client with that username.");
}


void Application::viewTask(unsigned num) const {
	const User* curEmployee = getLoggedUser();
	if (const Employee* cur = dynamic_cast<const Employee*>(curEmployee)) {
		MyString clientUsername =  cur->viewTask(num);
		int idx = getIdxOfClientByName(clientUsername);
		std::cout << "EGN: " << clientUsers[idx].getEGN() << std::endl << "Age: " << clientUsers[idx].getAge() << std::endl;
	}
}

void Application::list(const MyString& bankName) {
	int idx = getIdxOfBankByName(bankName);
	const User* curUser = getLoggedUser();
	banks[idx].list(curUser->getUsername());
}

void Application::approve(int n) {
	User* curEmployee = getLogedUser();
	if (Employee* cur = dynamic_cast<Employee*>(curEmployee)) {
		Task curTask = cur->getTaskAtIdx(n);
		if (curTask.getType() == "Open") {
			openEmpl(curTask.getUsername(), curTask.getCurBankName());
		}
		else if (curTask.getType() == "Close") {
			closeEmpl(curTask.getUsername(), curTask.getCurBankName(), curTask.getAccNum());
		}
		else if (curTask.getType() == "Change") {
			if (curTask.getIsValidated()) {
				changeEmpl(curTask.getUsername(), curTask.getNewBankName(), curTask.getCurBankName(), curTask.getAccNum());
			}
			else {
				std::cout << "You shold validate first. \n";
			}
		}
		cur->finishTaskAtIdx(n);
	}
}

void Application::disapprove(int id, const MyString& mess) {
	User* curEmployee = getLogedUser();
	if (Employee* cur = dynamic_cast<Employee*>(curEmployee)) {
		Task curTask = cur->getTaskAtIdx(id);
		int idxCl = getIdxOfClientByName(curTask.getUsername());
		clientUsers[idxCl].sendMessage(mess);
		cur->finishTaskAtIdx(id);
	}
}

bool Application::validate(int idx) {
	return true;
}

void Application::sendCheck(double sum, const MyString& verificationCode, const MyString& egn) {
	Check check(verificationCode, sum, getLoggedUser()->getUsername());
	int idx = getIdxOfClientByEgn(egn);
	clientUsers[idx].addCheck(check);
}

void Application::redeem(const MyString& bankName, unsigned accountNumber, const MyString& verificationCode) {
	User* curClient = getLogedUser();
	if (Client* cur = dynamic_cast<Client*>(curClient)) {
		int moneyToAdd = cur->redeem(verificationCode);
		int idx = getIdxOfBankByName(bankName);
		banks[idx].addMoneyToBankAcc(accountNumber, cur->getUsername(), moneyToAdd);
	}
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
}
