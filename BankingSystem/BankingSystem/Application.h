#pragma once
#include "Bank.h"
#include "DynamicArray.hpp"
#include "User.h"
#include "Client.h"
#include "Employee.h"
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
	void registerEmployee(Employee&& employee);
	void registerThirdParty(ThirdParty&& thirdParty);

	void login(const MyString& username, const MyString& password);
	void login(MyString&& username, MyString&& password);
	void logout();

	const User* getLoggedUser() const;
	User* getLoggedUser();
	LoggedUserType getType() const;
	bool doesUserAlreadyExist(User&& user) const;

private:
	DynamicArray<Bank> banks;
	DynamicArray<ThirdParty> thirdPartyUsers;
	User* logged = nullptr;


	Application() = default;
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
};