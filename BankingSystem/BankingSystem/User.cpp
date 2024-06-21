#include "User.h"
#include <fstream>

User::User(const MyString& username, const MyString& egn, unsigned age, const MyString& password) :
	username(username), egn(egn), age(age), password(password) {}

const MyString& User::getUsername() const {
	return username;
}

void User::saveToFile(std::ofstream& ofs) const {
	username.saveToFile(ofs);
	egn.saveToFile(ofs);
	ofs.write((const char*)&age, sizeof age);
	password.saveToFile(ofs);
}

void User::readFromFile(std::ifstream& ifs) {
	username.readFromFile(ifs);
	egn.readFromFile(ifs);
	ifs.read((char*)&age, sizeof age);
	password.readFromFile(ifs);
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
