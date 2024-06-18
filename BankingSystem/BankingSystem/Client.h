#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
#include "Bank.h"
#include "Account.h"
#include "Pair.hpp"
#include "Check.h"

class Client : public User {
private:
	DynamicArray<MyString> messages;
	DynamicArray<Pair<Bank, Account>> bankAccounts;
public:
	Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password);
};