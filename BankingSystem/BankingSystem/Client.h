#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
#include "Account.h"
#include "User.h"
#include "Pair.hpp"
#include "Check.h"
#include "Bank.h"

class Client : public User {
private:
	DynamicArray<MyString> messages;
	DynamicArray<Pair<MyString, Account>> bankAccounts; // format: {bankName: Account[account number, ballance]}
	//DynamicArray<Account> bankAccounts;
public:
	Client() = default;
	Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password);

	//User* clone() const override;
};