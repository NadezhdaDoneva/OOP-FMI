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
	void viewTask(unsigned num) const;

	void addTask(const Task& task);
	//User* clone() const override;
	//add task

private:
	MyString bankName;
	DynamicArray<Task> tasks;
};