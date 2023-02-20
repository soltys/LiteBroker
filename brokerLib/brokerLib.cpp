#include "include/brokerLib.h"

#include <iostream>

#include "SQLiteCpp/SQLiteCpp.h"

void brokerLib_init()
{
	std::cout << "brokerLib_init()" << std::endl;
	std::cout << SQLite::getLibVersion() << std::endl;
	std::cout << "/brokerLib_init()" << std::endl;
}
