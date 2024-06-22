#include "CommandRun.h"
#include "HandleClientCommand.h"
#include "HandleNoneCommand.h"

void RunCommand::execute(Application* app) {
	//TO DO: after having handleClientCommand, handleEmployeeCommand, handleThirdPartyCommand, handleNoneCommand 
	LoggedUserType type = app->getType();
	HandleNoneCommand handleNone;
	HandleClientCommand handleClient;

	switch (type)
	{
	case LoggedUserType::none: handleNone.execute(app); break;
	case LoggedUserType::client: handleClient.execute(app); break;
	default:
		break;
	}

}
