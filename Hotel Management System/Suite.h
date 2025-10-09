#pragma once

#include "Room.h"
#include <string>
#include<sstream>

/**
 * @brief Concrete class representing a Suite room.
 * @details Inherits from the Room base class and implements specific behavior for suite hotel rooms.
 * A suite offers luxury accommodations and may include optional premium features like a jacuzzi.
 */
class Suite : public Room {
	double jacuzzi_cost; ///< Additional cost for the jacuzzi feature, if present.
	bool has_jacuzzi;    ///< Flag indicating whether the suite has a jacuzzi.

public:
	/**
	 * @brief Default constructor.
	 * @details Creates a Suite with default values, initializing jacuzzi_cost to 0.0 and has_jacuzzi to false.
	 */
	Suite();

	/**
	 * @brief Parameterized constructor for Suite.
	 * @param room_number The unique identifier for the suite.
	 * @param price The base price per night for the suite.
	 * @param status The initial status of the suite (Available, Occupied, Maintenance).
	 * @param has_jac Flag indicating whether the suite includes a jacuzzi.
	 * @param jac_cost The additional cost for the jacuzzi feature.
	 */
	Suite(int room_number, double price, const std::string& status, bool has_jac, double jac_cost);

	/**
	 * @brief Gets the type of the room.
	* @return string Always returns "suite" for Suite objects.
	 */
	std::string getType() const override { return "suite"; }

	/**
	 * @brief Calculates the total price per night.
	 * @details The total price is the sum of the base room price and the jacuzzi cost (if applicable).
	 * @return double The total price per night including optional jacuzzi cost.
	 */
	double getTotalPrice() const override { return Room::getBasePrice() + (has_jacuzzi ? getJacuzziCost() : 0); }
	/**
	 * @brief Checks.
	 * @return bool The .
	 */
	bool hasJacuzzi()const { return has_jacuzzi; }
	/**
	 * @brief Checks if suite has jacuzzi.
	 * @return bool has_jac Flag indicating whether the suite includes a jacuzzi.
	 */
	double getJacuzziCost() const { return jacuzzi_cost; }

	/**
	 * @brief Serializes the Suite object into a formatted string representation.
	 * @details Extends the base Room::toString() method by appending suite-specific information.
	 *          The final format is: "room_number,status,suite,base_price,jacuzzi_cost"
	* @return string A comma-separated string containing the suite's complete data.
	 */
	std::string toString() const override;

	/**
	 * @brief Prints detailed information about the suite.
	 * @details Calls the base Room print method and adds suite-specific details
	 * including room type, total price, and jacuzzi cost (if applicable), formatted for console output.
	 */
	void printRoomInfo() const override;
};