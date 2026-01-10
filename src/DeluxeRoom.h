#pragma once

#include "Room.h"
#include <string>
#include<sstream>
/**
 * @brief Concrete class representing a Deluxe Room.
 * @details Inherits from the Room base class and implements specific behavior for deluxe hotel rooms.
 * A deluxe room offers premium amenities and includes additional extra fees on top of the base price.
 */
class DeluxeRoom : public Room {
	double extra_fees; ///< Additional fees for premium amenities and services.

public:
	/**
	 * @brief Default constructor.
	 * @details Creates a DeluxeRoom with default values, initializing extra_fees to 0.0.
	 */
	DeluxeRoom();

	/**
	 * @brief Parameterized constructor for DeluxeRoom.
	 * @param room_number The unique identifier for the room.
	 * @param price The base price per night for the deluxe room.
	 * @param status The initial status of the room (Available, Maintenance).
	 * @param extra_fees The additional fees for premium amenities and services.
	 */
	DeluxeRoom(int room_number, double price, const std::string& status, double extra_fees);

	/**
	 * @brief Gets the type of the room.
	* @return string Always returns "deluxe" for DeluxeRoom objects.
	 */
	std::string getType() const override { return "deluxe"; }

	/**
	 * @brief Sets the extra fees for premium amenities.
	 * @param fees The new amount for extra fees.
	 */
	void setExtraFees(double fees) { extra_fees = fees; }

	/**
	 * @brief Gets the current extra fees amount.
	 * @return double The additional fees for premium amenities and services.
	 */
	double getExtraFees() const { return extra_fees; }

	/**
	 * @brief Calculates the total price per night.
	 * @details The total price is the sum of the base room price and the extra fees.
	 * @return double The total price per night including extra fees.
	 */
	double getTotalPrice() const override { return Room::getBasePrice() + getExtraFees(); }

	/**
	 * @brief Serializes the DeluxeRoom object into a formatted string representation.
	 * @details Extends the base Room::toString() method by appending deluxe room-specific information.
	 *          The final format is: "room_number,status,deluxe,base_price,extra_fees"
	* @return string A comma-separated string containing the room's complete data.
	 */
	std::string toString() const;

	/**
	 * @brief Prints detailed information about the deluxe room.
	 * @details Calls the base Room print method and adds deluxe room-specific details
	 * including room type, total price, base price, and extra fees, formatted for console output.
	 */
	void printRoomInfo() const;
};