#include "Client.h"
#include <fstream>

Client::Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password)
	 : User(username, egn, age, password){}

void Client::check_avl(const MyString& bankName, const MyString& accountNumber) {

}

void Client::saveToFile(std::ofstream& ofs) const {
	User::saveToFile(ofs);
	int messCount = messages.getSize();
	ofs.write((const char*)&messCount, sizeof messCount);
	for (int i = 0; i < messCount; i++) {
		messages[i].saveToFile(ofs);
	}
	int bankAccountsCount = bankAccounts.getSize();
	ofs.write((const char*)&bankAccountsCount, sizeof bankAccountsCount);
	for (int i = 0; i < bankAccountsCount; i++) {
		bankAccounts[i].getLhs().saveToFile(ofs);
		bankAccounts[i].getRhs().saveToFile(ofs);
	}
}

void Client::readFromFile(std::ifstream& ifs) {
	User::readFromFile(ifs);
	int messCount = 0;
	ifs.read((char*)&messCount, sizeof messCount);
	for (int i = 0; i < messCount; i++) {
		ifs.read((char*)&messages[i], sizeof messages[i]);
	}
	int bankAccountsCount = 0;
	ifs.read((char*)&bankAccountsCount, sizeof bankAccountsCount);
	for (int i = 0; i < bankAccountsCount; i++) {
		ifs.read((char*)&bankAccounts[i].getLhs(), sizeof bankAccounts[i].getLhs());
		bankAccounts[i].getRhs().readFromFile(ifs);
	}
}

//User* Client::clone() const {
//	return new Client(*this);
//}
