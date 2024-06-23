#pragma once
#include "User.h"

class ThirdParty : public User {
public:
	ThirdParty() = default;
	ThirdParty(const MyString& username, const MyString& egn, unsigned age, const MyString& password);
};