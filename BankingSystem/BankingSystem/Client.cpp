#include "Client.h"

Client::Client(const MyString& username, const MyString& egn, unsigned age, const MyString& password)
	 : User(username, egn, age, password){}

void Client::check_avl(const MyString& bankName, const MyString& accountNumber) {

}

//User* Client::clone() const {
//	return new Client(*this);
//}
