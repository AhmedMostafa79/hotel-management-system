#include<iostream>
#include "HotelSystem.h"
#include "MySQLDatabase.h"
#include "DatabaseConfig.h"

int main() {
	try {

	DatabaseConfig config=DatabaseConfig::loadFromFile("DatabaseConfig.txt");
	HotelSystem hotel(config);
	hotel.run();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}