#include "CommandWhoAmI.h"

int WhoAmICommand::execute() {
    app->whoami();
	LoggedUserType loggedUserType = app->getType();

	switch (loggedUserType)
	{
	case LoggedUserType::client:
		return 1;
	case LoggedUserType::employee:
		return 2;
	case LoggedUserType::thirdParty:
		return 3;
	}
}
