#include <string>
#include <sstream>
#include <iostream>
#include "DeluxeRoom.h"
//Constructors Definition
DeluxeRoom::DeluxeRoom() : extra_fees(0.0) {}

DeluxeRoom::DeluxeRoom(int room_number, double price, const std::string& status, double extra_fees)
	: Room(room_number, price, status), extra_fees(extra_fees) {
}
//Public Functions Definition
std::string DeluxeRoom::toString() const {
	std::ostringstream room_info;
	room_info << getType() << "," << std::to_string(Room::getBasePrice()) << "," << getExtraFees();
	return Room::toString() + "," + room_info.str();
}

void DeluxeRoom::printRoomInfo() const {
	Room::printRoomInfo();
	std::cout << "\t\t\t Type: " << getType() << '\n';
	std::cout << "\t\t\t Price: " << getBasePrice() << '\n';
	std::cout << "\t\t\t Extra Fees: " << getExtraFees() << '\n';
}