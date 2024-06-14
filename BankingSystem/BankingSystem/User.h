#pragma once
#include "MyString.h"

class User {
public:
	User(const MyString& username, const MyString& egn, unsigned age, const MyString& password);
	User() = default;

	bool isValidPassword(const MyString& pass) const;
	/*void whoami();
	void help();*/
protected:
	MyString username = "Unknown";
	MyString egn = "Unknown";
	unsigned age = 0;
	MyString password = "Unknown";
};