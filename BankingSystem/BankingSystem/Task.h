#pragma once
#include "MyString.h"

class Task {
public:
	Task() = default;
	Task(const MyString& type, const MyString& taskName);
	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
private:
	MyString type = "Unknown";
	MyString taskName = "Unknown";
	//const Client* client = nullptr
	//MyString details
};