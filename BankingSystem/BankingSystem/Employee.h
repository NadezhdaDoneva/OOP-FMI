#pragma once
#include "MyQueue.hpp" 
#include "MyString.h"
#include "Task.h"
#include "User.h"


class Employee : public User {
public:
	Employee() = default;
	Employee(const MyString& username, const MyString& egn, unsigned age, const MyString& password, const MyString& bankName);
	
	int getTasksCount() const;

	//User* clone() const override;
	//add task

private:
	MyString bankName;
	MyQueue<Task> tasks;
};