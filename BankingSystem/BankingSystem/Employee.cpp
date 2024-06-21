#include "Employee.h"
#include <fstream>

Employee::Employee(const MyString& username, const MyString& egn, unsigned age, const MyString& password, const MyString& bankName)
	: User(username, egn, age, password), bankName(bankName) {}

int Employee::getTasksCount() const {
	return tasks.getSize();
}

void Employee::saveToFile(std::ofstream& ofs) const {
	User::saveToFile(ofs);
	bankName.saveToFile(ofs);
	int tasksCount = tasks.getSize();
	ofs.write((const char*)&tasksCount, sizeof tasksCount);
	for (int i = 0; i < tasksCount; i++) {
		tasks[i].saveToFile(ofs);
	}
}

void Employee::readFromFile(std::ifstream& ifs) {
	User::readFromFile(ifs);
	bankName.readFromFile(ifs);
	int tasksCount = 0;
	ifs.read((char*)&tasksCount, sizeof tasksCount);
	for (int i = 0; i < tasksCount; i++) {
		tasks[i].readFromFile(ifs);
	};
}

void Employee::addTask(const Task& task) {
	tasks.push(task);
}

//User* Employee::clone() const {
//	return new Employee(*this);
//}
