#include "HandleClientCommand.h"
#include "CommandClientChange.h"
#include "CommandClientCheckAvailable.h"
#include "CommandClientClose.h"
#include "CommandClientList.h"
#include "CommandClientMessages.h"
#include "CommandClientOpen.h"
#include "CommandClientRedeem.h"

void HandleClientCommand::execute(Application* app) {
	ChangeCommand changeC;
	CheckAvailableCommand checkAvlC;
	CloseCommand closeC;
	ListCommand listC;
	MessagesCommand messagesC;
	OpenCommand openC;
	RedeemCommand redeemC;

	int n;
	std::cout << "Choose: \n 1) open\n 2) close\n 3) check available\n 4) change\n 5) list\n 6) messages\n 7) redeem\n 8) logout 9) exit";
	std::cin >> n;

	switch (n)
	{
	case 1:
		openC.execute(app); break;
	case 2:
		closeC.execute(app); break;
	case 3: 
		checkAvlC.execute(app); break;
	case 4:
		changeC.execute(app); break;
	case 5:
		listC.execute(app); break;
	case 6:
		messagesC.execute(app); break;
	case 7:
		redeemC.execute(app); break;
	case 8:
		app->logout(); break;
	case 9:
		break;
	default:
		std::cout << "Unknown command!\n"; break;
	}
}
