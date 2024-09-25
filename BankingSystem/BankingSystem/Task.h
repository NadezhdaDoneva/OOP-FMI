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
	MyString view() const;
	const MyString& getType() const;
	const MyString& getUsername() const;
	const MyString& getCurBankName() const;
	const MyString& getNewBankName() const;
	unsigned getAccNum() const;
	bool getIsValidated() const;
	void setValidated();
private:
	MyString type = "Unknown";
	MyString username = "Unknown";
	MyString curBankName = "Unknown";
	MyString newBankName = "Unknown";
	unsigned accountNumber = 0;
	bool isValidated = false;
};