#include <sstream>
#include <string>
#include "Room.h"
#include<iostream>
// use std:: explicitly

//Constructor Definition
Room::Room() : room_number(-1), base_price(0) {}
Room::Room(int room_number, double price, const std::string& status)
	: room_number(room_number), base_price(price), status(status) {
}
std::string Room::toString() const {
	std::ostringstream room_info;
	room_info << std::to_string(getNumber()) << "," << getStatus();
	return room_info.str();
}

void Room::printRoomInfo() const {
	std::cout << "\n";
	std::cout << "\t\t\t number: " << getNumber() << "\n";
	std::cout << "\t\t\t status: " << getStatus() << "\n";
}

