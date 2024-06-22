#pragma once
#include "MyString.h"

class User {
public:
	User(const MyString& username, const MyString& egn, unsigned age, const MyString& password);
	User() = default;

	const MyString& getUsername() const;
	const MyString& getEGN() const;
	unsigned getAge() const;

	/*virtual User* clone() const = 0;
	virtual ~User() = default;*/

	virtual void saveToFile(std::ofstream& ofs) const;
	virtual void readFromFile(std::ifstream& ifs);

	bool isValidPassword(const MyString& pass) const;
	void whoami();
	void help();
protected:
	MyString username = "Unknown";
	MyString egn = "Unknown";
	unsigned age = 0;
	MyString password = "Unknown";
};