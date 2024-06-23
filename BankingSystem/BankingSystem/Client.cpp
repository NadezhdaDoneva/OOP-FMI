#include "Client.h"
#include <fstream>
//#include "UtilFuncs.h"

Client::Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password)
	 : User(username, egn, age, password){}

int Client::getIdxOfCheckByCode(const MyString& code) const {
	int countOfChecks = checks.getSize();
	if (countOfChecks == 0) {
		std::cout << "there are no checks to be redeemed yet.";
	}
	for (int i = 0; i < countOfChecks; i++) {
		if (checks[i].getCode() == code) {
			return i;
		}
	}
	throw std::runtime_error("No check with that code.");
}

void Client::printMessages() const {
	int messagesCount = messages.getSize();
	for (size_t i = 0; i < messagesCount; i++) {
		std::cout << messages[i];
	}
}

void Client::sendMessage(const MyString& mess) {
	messages.pushBack(mess);
}

double Client::redeem(const MyString& verificationCode) {
	int idx = getIdxOfCheckByCode(verificationCode);
	return checks[idx].getMoney();
}

void Client::addCheck(const Check& check) {
	checks.pushBack(check);
	MyString mess = "You have a check assigned to you by " + check.getNameOfThirdParty() + "\n";
	sendMessage(mess);
}

void Client::saveToFile(std::ofstream& ofs) const {
	User::saveToFile(ofs);
	int messCount = messages.getSize();
	ofs.write((const char*)&messCount, sizeof messCount);
	for (int i = 0; i < messCount; i++) {
		messages[i].saveToFile(ofs);
	}

	int checksCount = checks.getSize();
	ofs.write((const char*)&checksCount, sizeof checksCount);
	for (int i = 0; i < checksCount; i++) {
		checks[i].saveToFile(ofs);
	}
}

void Client::readFromFile(std::ifstream& ifs) {
	User::readFromFile(ifs);
	int messCount = 0;
	ifs.read((char*)&messCount, sizeof messCount);
	for (int i = 0; i < messCount; i++) {
		ifs.read((char*)&messages[i], sizeof messages[i]);
	}
	
	int  checksCount = 0;
	ifs.read((char*)&checksCount, sizeof checksCount);
	for (int i = 0; i < checksCount; i++) {
		checks[i].readFromFile(ifs);
	}
}
