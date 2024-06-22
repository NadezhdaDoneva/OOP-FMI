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

void Task::print() const {
	if (type == "Open") {
		std::cout << "Open - " << username << " wants to create an account." << std::endl;
	}
	else if (type == "Close") {
		std::cout << "Close - " << username << " wants to close an account." << std::endl;
	}
	else if (type == "Change") {
		std::cout << "Change - " << username << " wants to join." << newBankName << std::endl;
	}
}


MyString Task::view() const {
	std::cout << type << " request from: " << std::endl;
	std::cout << "Name: " << username << std::endl;
	return username;
}

const MyString& Task::getType() const {
	return type;
}

const MyString& Task::getUsername() const {
	return username;
}

const MyString& Task::getCurBankName() const {
	return curBankName;
}

const MyString& Task::getNewBankName() const {
	return newBankName;
}

unsigned Task::getAccNum() const {
	return accountNumber;
}
