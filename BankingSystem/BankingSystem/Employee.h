#pragma once
#include "DynamicArray.hpp"
#include "MyString.h"
#include "Task.h"
#include "User.h"


class Employee : public User {
public:
	Employee() = default;
	Employee(const MyString& username, const MyString& egn, unsigned age, const MyString& password, const MyString& bankName);
	
	int getTasksCount() const;

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;

	void printTasks() const;
	MyString viewTask(unsigned num) const;

	void addTask(const Task& task);
	const Task& getTaskAtIdx(int n) const;
	void finishTaskAtIdx(int n);
	void validateTask(int idx);

private:
	MyString bankName;
	DynamicArray<Task> tasks;
};