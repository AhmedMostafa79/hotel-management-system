#pragma once

#include<string>

/**
  * @class Room
  * @brief Represents a hotel room with its properties and state.
  *
  * This class encapsulates all the attributes and behaviors of a hotel room,
  * including its unique identifier, pricing, type, and current status.
  * It provides functionality to manage room details, calculate costs,
  * and serialize room information for storage and display.
  */

class Room {
	int room_number;        ///< Unique ID for the room.
	double base_price; ///< Cost for one night's stay in the room.
	std::string status;          ///< Current state (e.g. Available, Occupied, Maintenance).
public:
	/**
	 * @brief Default Constructor.
	 * @details provides empty room object.
	 */
	Room();
	/**
	 * @brief Parameterized constructor. Creates a room with specified properties.
	 * @param room_num The unique number identifying the room.
	 * @param price The cost per night for the room.
	 * @param status The initial status of the room.
	 */
	Room(int room_number, double price, const std::string& status);

	/**
	 * @brief Virtual destructor.
	 * @details Ensures proper cleanup for derived class objects when deleted through base class pointer.
	 */
	virtual ~Room() {};

	/**
	 * @brief Pure virtual function to get room type.
	 * @details Must be implemented by derived classes to return their specific room type.
	 * @return string The type of the room (e.g., "Standard", "Deluxe", "Suite").
	 */
	virtual  std::string getType()const = 0;
	/**
	 * @brief Gets price per night of the room.
	 * @return double the price.
	 * @virtual
	 */
	virtual double getBasePrice()const { return base_price; }
	/**
	 * @brief Calculates the total price of the room
	 * @return Total price as double
	 * @virtual
	 */
	virtual double getTotalPrice()const =0;
	/**
	 * @brief Sets price per night for the room.
	 * @param price_ The new price per night.
	 */
	void setPrice(double price_) { this->base_price = price_; }

	/**
	 * @brief Sets the new status of the room.
	 * @param status The new Status(Available, Maintenance).
	 */
	void setStatus(const std::string& status) { this->status = status; }

	/**
	 * @brief Gets status of the room
	 * @return Const string& a constant reference to the status string.
	 */
	const std::string& getStatus() const { return this->status; }

	bool isRoomAvailable()const { return status == "available"; }
	/**
	 * @brief Gets the room's unique identifier number.
	 * @return int the room number.
	 */
	int getNumber() const { return this->room_number; }

	/**
	 * @brief Serializes the Room object into string representation.
	 * @details the format is : "room_number,type,status,price_per_night".
	 * @return string a comma-separated string containing the room's data.
	 */
	virtual std::string toString()const;
	/**
	 * @brief prints the room details to the standard output.
	 * @details the output is indented and formatted for console display in a formatted way.
	 */
	virtual void printRoomInfo() const;
};
