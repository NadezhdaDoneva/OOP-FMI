#pragma once
#include "User.h"

class ThirdParty : public User {
public:
	User* clone() const override;
};