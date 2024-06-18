#include "Account.h"
#include <cstdlib> 
#include <time.h>
Account::Account() {
	srand(time(NULL));
	accountNumber = rand();
}
