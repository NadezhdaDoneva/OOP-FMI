#include "Client.h"
#include <fstream>

Client::Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password)
	 : User(username, egn, age, password){}

int Client::IdxOfBankWithThatAccountNum(const MyString& bankName, unsigned accountNumber) const {
	int countOfAccounts = bankAccounts.getSize();
	if (countOfAccounts == 0) {
		throw std::runtime_error("You have no accounts");
	}
	for (int i = 0; i < countOfAccounts; i++) {
		MyString curBankName = bankAccounts[i].getLhs();
		Account curAcc = bankAccounts[i].getRhs();
		if (curBankName == bankName && curAcc.getAccountNumber() == accountNumber) {
			return i;
		}
	}
	return -1;
}

double Client::checkAvailable(const MyString& bankName, unsigned accountNumber) const {
	int idx = IdxOfBankWithThatAccountNum(bankName, accountNumber);
	if (idx == -1) {
		throw std::runtime_error("No such bank and accountNumber.");
	}
	else {
		return bankAccounts[idx].getRhs().getBalance();
	}
}

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
	return -1;
}

void Client::redeem(const MyString& bankName, unsigned accountNumber, const MyString& verificationCode) {
	int idxBankAccount = IdxOfBankWithThatAccountNum(bankName, accountNumber);
	if (idxBankAccount != -1) {
		int idxCheck = getIdxOfCheckByCode(verificationCode);
		if (idxCheck != -1) {
			bankAccounts[idxBankAccount].getRhs().addMoney(checks[idxCheck].getMoney());
		}
		else {
			throw std::runtime_error("Wrong code.");
		}
	}
	else {
		throw std::runtime_error("No such account with that bankname and account number.");
	}
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
	int bankAccountsCount = 0;
	ifs.read((char*)&bankAccountsCount, sizeof bankAccountsCount);
	for (int i = 0; i < bankAccountsCount; i++) {
		ifs.read((char*)&bankAccounts[i].getLhs(), sizeof bankAccounts[i].getLhs());
		bankAccounts[i].getRhs().readFromFile(ifs);
	}
	int  checksCount = 0;
	ifs.read((char*)&checksCount, sizeof checksCount);
	for (int i = 0; i < checksCount; i++) {
		checks[i].readFromFile(ifs);
	}
}

//User* Client::clone() const {
//	return new Client(*this);
//}
