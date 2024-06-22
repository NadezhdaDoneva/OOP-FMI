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

void Employee::printTasks() const {
	int tasksCount = tasks.getSize();
	for (int i = 0; i < tasksCount; i++) {
		std::cout << "[" << i << "] ";
		tasks[i].print();
	}
}

MyString Employee::viewTask(unsigned num) const {
	if (num > tasks.getSize()) {
		throw std::runtime_error("no task with that id.");
	}

	MyString clientUsername = tasks[num].view();
	return clientUsername;
}

void Employee::addTask(const Task& task) {
	tasks.pushBack(task);
}

const Task& Employee::getTaskAtIdx(int n) const {
	if (n < 0 || n > tasks.getSize()) {
		throw std::runtime_error("Unvalid task idx");
	}
	return tasks[n];
}

//User* Employee::clone() const {
//	return new Employee(*this);
//}
