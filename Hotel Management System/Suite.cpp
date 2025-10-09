#include <sstream>
#include <iostream>
#include <string>
#include "Suite.h"
// use std:: explicitly
// Constructors Definition
Suite::Suite() : jacuzzi_cost(0.0), has_jacuzzi(false) {}
Suite::Suite(int room_number, double price, const std::string& status, bool has_jac, double jac_cost)
	: Room(room_number, price, status), has_jacuzzi(has_jac), jacuzzi_cost(jac_cost) {
}
std::string Suite::toString() const {
	std::ostringstream room_info;
	room_info << getType() << "," << std::to_string(Room::getBasePrice()) << "," << getJacuzziCost();
	return Room::toString() + "," + room_info.str();
}
void Suite::printRoomInfo() const {
	Room::printRoomInfo();
	std::cout << "\t\t\t Type: " << getType() << '\n';
	std::cout << "\t\t\t Price: " << getBasePrice() << '\n';
	if (has_jacuzzi)
		std::cout << "\t\t\t Jacuzzi Cost: " << getJacuzziCost() << '\n';
}