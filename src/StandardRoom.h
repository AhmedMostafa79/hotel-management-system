#pragma once

#include "Room.h"
#include <string>
#include<sstream>

/**
 * @brief Concrete class representing a Standard Room.
 * @details Inherits from the Room base class and implements specific behavior for standard hotel rooms.
 * A standard room typically offers basic amenities at a lower price point.
 */
class StandardRoom : public Room {
public:
	/**
	 * @brief Default constructor.
	 * @details Creates a StandardRoom with default values by calling the base Room default constructor.
	 */
	StandardRoom() {}

	/**
	 * @brief Parameterized constructor for StandardRoom.
	 * @param room_number The unique identifier for the room.
	 * @param price The price per night for the standard room.
	 * @param status The initial status of the room (Available, Maintenance).
	 */
	StandardRoom(int room_number, double price, const std::string& status);

	/**
	 * @brief Gets the type of the room.
	* @return string Always returns "standard" for StandardRoom objects.
	 */
	std::string getType() const override { return "standard"; }
	double getTotalPrice()const override { return Room::getBasePrice(); }
	/**
	 * @brief Serializes the StandardRoom object to a string.
	 * @details Extends the base Room toString() by appending room type and price information.
	* @return string A comma-separated string in the format: "room_number,status,standard,price"
	 */
	std::string toString() const override;

	/**
	 * @brief Prints detailed information about the standard room.
	 * @details Calls the base Room print method and adds standard room-specific details
	 * including room type and price, formatted for console output.
	 */
	void printRoomInfo() const override;
};