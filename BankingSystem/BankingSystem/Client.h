#pragma once
#include "MyString.h"
#include "DynamicArray.hpp"
//#include "Account.h"
#include "User.h"
//#include "Pair.hpp"
#include "Check.h"
#include "Bank.h"
//#include "UtilFuncs.h"

class Client : public User {
private:
	DynamicArray<Check> checks;
	DynamicArray<MyString> messages;
public:
	Client() = default;
	Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password);

	int getIdxOfCheckByCode(const MyString& code) const;
	
	void printMessages() const;
	void sendMessage(const MyString& mess);
	double redeem(const MyString& verificationCode);
	void addCheck(const Check& check);

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
};