#pragma once
#include "MyString.h"

class Task {
public:
	Task() = default;
	Task(const MyString& type, const MyString& username, const MyString& curBankName);
	Task(const MyString& type, const MyString& username, const MyString& curBankName, unsigned accountNumber);
	Task(const MyString& type, const MyString& username, const MyString& curBankName, const MyString& newBankName, unsigned accountNumber);
	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
	void print() const;
	void view() const;
private:
	MyString type = "Unknown";
	MyString username = "Unknown";
	MyString curBankName = "Unknown";
	MyString newBankName = "Unknown";
	unsigned accountNumber = 0;
	//const Client* client = nullptr
	//MyString details
};