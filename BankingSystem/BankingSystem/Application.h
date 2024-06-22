#pragma once
#include "Bank.h"
#include "DynamicArray.hpp"
#include "User.h"
#include "Client.h"
#include "ThirdParty.h"
#include "Check.h"

enum class LoggedUserType {
	client,
	employee,
	thirdParty,
	none
};

class Application {
public:
	Application() = default;
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;

	static Application& getInstance();

	const DynamicArray<Bank>& getBanks() const;

	void registerClient(Client&& client);
	void registerEmployee(Employee&& employee, const MyString& bankName);
	void registerThirdParty(ThirdParty&& thirdParty);

	void login(const MyString& username, const MyString& password);
	void logout();
	void whoami();
	void help();

	const User* getLoggedUser() const;
	User* getLogedUser();
	LoggedUserType getType() const;
	bool doesUserAlreadyExist(User&& user) const;
	int getIdxOfBankByName(const MyString& bankName) const;
	int getIdxOfClientByName(const MyString& username) const;

	void createBank(const MyString& bankName);
	void openCl(const MyString& bankName);
	void closeCl(const MyString& bankName, unsigned accountNumber);
	void changeCl(const MyString& newBankName, const MyString& curBankName, unsigned accountNumber);

	void openEmpl(const MyString& username, const MyString& bankName);
	void closeEmpl(const MyString& username, const MyString& bankName, unsigned accountNumber);
	void changeEmpl(const MyString& username, const MyString& newBankName, const MyString& curBankName, unsigned accountNumber);
	void viewTask(unsigned num) const;
	void approve(int n);
	void disapprove(int id, const MyString& mess);
	//void redeem(const MyString& bankName, unsigned accountNumber, const MyString& verificationCode);

	void addClient(const Client& client);
	void addClient(Client&& client);
	void addThirdParty(const ThirdParty& thirdParty);
	void addThirdParty(ThirdParty&& thirdParty);

	void save() const;
	void load();
private:
	DynamicArray<Bank> banks;
	DynamicArray<ThirdParty> thirdPartyUsers;
	DynamicArray<Client> clientUsers;
	//DynamicArray<Check> checks;
	//DynamicArray<PolymorphicPtr><User> users
	User* logged = nullptr;
	LoggedUserType type = LoggedUserType::none;

};