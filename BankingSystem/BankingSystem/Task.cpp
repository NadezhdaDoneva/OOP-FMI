#include "Task.h"
#include <fstream>

Task::Task(const MyString& type, const MyString& username, const MyString& curBankName) {
	this->type = type;
	this->username = username;
	this->curBankName = curBankName;
}

Task::Task(const MyString& type, const MyString& username, const MyString& curBankName, unsigned accountNumber) {
	this->type = type;
	this->username = username;
	this->curBankName = curBankName;
	this->accountNumber = accountNumber;
}

Task::Task(const MyString& type, const MyString& username, const MyString& curBankName, const MyString& newBankName, unsigned accountNumber) {
	this->type = type;
	this->username = username;
	this->curBankName = curBankName;
	this->newBankName = newBankName;
	this->accountNumber = accountNumber;
}

void Task::saveToFile(std::ofstream& ofs) const {
	type.saveToFile(ofs);
	username.saveToFile(ofs);
	curBankName.saveToFile(ofs);
	newBankName.saveToFile(ofs);
	ofs.write((const char*)&accountNumber, sizeof accountNumber);
}

void Task::readFromFile(std::ifstream& ifs) {
	type.readFromFile(ifs);
	username.readFromFile(ifs);
	curBankName.readFromFile(ifs);
	newBankName.readFromFile(ifs);
	ifs.read((char*)accountNumber, sizeof accountNumber);
}
