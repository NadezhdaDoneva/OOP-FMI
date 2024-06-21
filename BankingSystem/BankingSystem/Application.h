#pragma once
#include "Bank.h"
#include "DynamicArray.hpp"
#include "User.h"
#include "Client.h"
#include "ThirdParty.h"

enum class LoggedUserType {
	client,
	employee,
	thirdParty,
	none
};

class Application {
public:
	static Application& getInstance();

	const DynamicArray<Bank>& getBanks() const;

	void registerClient(Client&& client);
	void registerEmployee(Employee&& employee, const MyString& bankName);
	void registerThirdParty(ThirdParty&& thirdParty);

	void login(const MyString& username, const MyString& password);
	void login(MyString&& username, MyString&& password);
	void logout();
	void whoami();
	void help();

	const User* getLoggedUser() const;
	User* getLoggedUser();
	LoggedUserType getType() const;
	bool doesUserAlreadyExist(User&& user) const;
	int getIdxOfBankByName(const MyString& bankName) const;

	void createBank(const MyString& bankName);

	void addClient(const Client& client);
	void addClient(Client&& client);
	void addThirdParty(const ThirdParty& thirdParty);
	void addThirdParty(ThirdParty&& thirdParty);

	Application() = default;
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;

private:
	DynamicArray<Bank> banks;
	DynamicArray<ThirdParty> thirdPartyUsers;
	DynamicArray<Client> clientUsers;
	//DynamicArray<PolymorphicPtr><User> users
	User* logged = nullptr;
	LoggedUserType type = LoggedUserType::none;

};