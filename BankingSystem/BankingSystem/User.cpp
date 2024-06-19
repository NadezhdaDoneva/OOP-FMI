#include "User.h"


User::User(const MyString& username, const MyString& egn, unsigned age, const MyString& password) :
	username(username), egn(egn), age(age), password(password) {}

const MyString& User::getUsername() const {
	return username;
}

bool User::isValidPassword(const MyString& pass) const
{
	return pass == password;
}

void User::whoami() {
	std::cout << "You are " << username << ".\n";
}

void User::help() {
	//cout the commands list
}
