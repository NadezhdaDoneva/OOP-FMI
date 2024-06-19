#include "ThirdParty.h"

//User* ThirdParty::clone() const {
//    return new ThirdParty(*this);
//}

ThirdParty::ThirdParty(const MyString& username, const MyString& egn, unsigned age, const MyString& password)
	: User(username, egn, age, password) {}
