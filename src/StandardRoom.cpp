#include<string>
#include<sstream>
#include<iostream>
#include "StandardRoom.h"
// use std:: explicitly

//Constructors  Definition

StandardRoom::StandardRoom(int room_number, double price, const std::string& status)
	: Room(room_number, price, status) {
}
//Public Functions Defintion
std::string StandardRoom::toString() const {
	std::ostringstream room_info;
	room_info << getType() << "," << std::to_string(getBasePrice());
	return Room::toString() + "," + room_info.str();
}
void StandardRoom::printRoomInfo() const {
	Room::printRoomInfo();
	std::cout << "\t\t\t Type: " << getType() << '\n';
	std::cout << "\t\t\t Price: " << getBasePrice() << '\n';
}