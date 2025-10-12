#pragma once

#include "Room.h"
#include "HotelManager.h"
#include<optional>
#include <string>
/**
  * @class HotelUI
  * @brief User interface class for interacting with the hotel management system.
  *
  * This class provides a comprehensive user interface for all hotel operations,
  * including room management, customer management, booking operations, and
  * display functionalities. It serves as the presentation layer that interacts
  * with users through the console while delegating business logic to HotelManager.
  */
class HotelUI {
	HotelManager& hotel_manager;    ///< Reference to the hotel manager for business operations.

	/**
	 * @brief Gets reference to the hotel manager.
	 * @return HotelManager& Reference to the hotel manager.
	 */
	HotelManager& getHotelManager();
	const HotelManager& getHotelManager()const;
	void printRooms(const std::vector<std::unique_ptr<Room>>& rooms)const;

public:
	/**
	 * @brief Constructor.
	 * @param manager Reference to the HotelManager instance.
	 */
	HotelUI(HotelManager& manager);

	/**
	 * @brief Displays available rooms for given dates.
	 * @param chin Check-in date.
	 * @param chout Check-out date.
	 */
	void printAvailableRoomsUI(const DateTime& chin, const DateTime& chout) const;

	/**
	 * @brief Prints rooms filtered by status.
	 */
	void printRoomsByStatusUI()const;

	/**
	 * @brief Prints rooms filtered by type.
	 */
	void printRoomsByTypeUI()const;

	/**
	 * @brief Displays all rooms in the system.
	 */
	void printAllRoomsUI() const;

	/**
	 * @brief Displays all customers in the system.
	 */
	void printAllCustomersUI() const;

	/**
	 * @brief Displays all bookings in the system.
	 */
	void printAllBookingsUI() const;

	/**
	 * @brief Displays room details by room number.
	 */
	void printRoomByNumberUI() const;

	/**
	 * @brief Displays customer details by customer ID.
	 */
	void printCustomerByIdUI() const;

	/**
	 * @brief Displays booking details by booking ID.
	 */
	void printBookingByIDUI() const;


	/**
	 * @brief Creates a standard room with given status and price.
	 */
	std::unique_ptr<Room>  readStandardRoomUI(const std::string& status, double price);

	/**
	 * @brief Creates a deluxe room with given status and price.
	 * @details Prompts user for additional fees input.
	 */
	std::unique_ptr<Room>  readDeluxeRoomUI(const std::string& status, double price);

	/**
	 * @brief Creates a suite with given status and price.
	 * @details Prompts user for jacuzzi availability and cost.
	 */
	std::unique_ptr<Room>  readSuiteUI(const std::string& status, double price);
	/**
	 * @brief Adds a new room through user interface.
	 */
	void addNewRoomUI();

	/**
	 * @brief Adds a new customer through user interface.
	 */
	void addNewCustomerUI();

	/**
	 * @brief Adds a new booking through user interface.
	 */
	void addNewBookingUI();

	/**
	 * @brief Deletes a room through user interface.
	 */
	void deleteRoomUI();

	/**
	 * @brief Deletes a customer through user interface.
	 */
	void deleteCustomerUI();

	/**
	 * @brief Deletes a booking through user interface.
	 */
	void deleteBookingUI();

	/**
	 * @brief Modifies room details through user interface.
	 */
	void modifyRoomUI();

	/**
	 * @brief Modifies customer details through user interface.
	 */
	void modifyCustomerUI();

	/**
	 * @brief Modifies booking details through user interface.
	 */
	void modifyBookingUI();
};