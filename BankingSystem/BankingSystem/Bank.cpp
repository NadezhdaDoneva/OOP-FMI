#include "Bank.h"

Bank::Bank(const MyString& name) : bankName(name){}

//const DynamicArray<Client>& Bank::getClients() const {
//    return this->clients;
//}

const DynamicArray<Employee>& Bank::getEmployees() const {
    return this->employees;
}

//void Bank::addClient(const Client& client) {
//    clients.pushBack(client);
//}
//
//void Bank::addClient(Client&& client){
//    clients.pushBack(std::move(client));
//}

void Bank::addEmployee(const Employee& employee) {
    employees.pushBack(employee);
}

void Bank::addEmployee(Employee&& employee) {
    employees.pushBack(std::move(employee));
}

Employee* Bank::getLeastBusiestEmployee() {
    int employeesCount = employees.getSize();
    if (employeesCount == 0) {
        throw std::runtime_error("No emplyees available.");
    }

    Employee* leastBusiest = &employees[0];
    for (int i = 0; i < employeesCount; i++) {
        if (employees[i].getTasksCount() < leastBusiest->getTasksCount()) {
            leastBusiest = &employees[i];
        }
    }
    return leastBusiest;
}

const MyString& Bank::getBankName() const {
    return bankName;
}
