#pragma once

#include<string>
#include "HotelManager.h"
#include "HotelUI.h"
#include "MySQLDatabase.h"
/**
  * @class HotelSystem
  * @brief Main system class that coordinates the entire hotel management application.
  *
  * This class serves as the entry point and central coordinator for the hotel management system.
  * It manages the interaction between the business logic (HotelManager) and user interface (HotelUI),
  * provides role-based access control, and orchestrates the complete menu navigation system
  * for administrators and receptionists.
  */
class HotelSystem {
	MySQLDatabase database;
	HotelManager hotel_manager;    ///< Manages all hotel business logic and data.
	HotelUI hotel_ui;              ///< Handles user interface and presentation layer.

	/**
	 * @brief Gets reference to the hotel UI.
	 * @return HotelUI& Reference to the hotel user interface.
	 */
	HotelUI& getHotelUI();

	/**
	 * @brief Gets reference to the hotel manager.
	 * @return HotelManager& Reference to the hotel manager.
	 */
	HotelManager& getHotelManager();

	/**
	 * @brief Displays admin room management menu.
	 */
	void showAdminRoomManagement();

	/**
	 * @brief Displays receptionist room operations menu.
	 */
	void showReceptionistRoomOperations();

	/**
	 * @brief Displays customer management menu.
	 */
	void showCustomerManagementMenu();

	/**
	 * @brief Displays booking management menu.
	 */
	void showBookingManagementMenu();

	/**
	 * @brief Displays admin main menu.
	 */
	void showAdminMenu();

	/**
	 * @brief Displays receptionist main menu.
	 */
	void showReceptionistMenu();
	bool isAdmin(const std::string& role)const;

	/**
	 * @brief Validates password for role-based access.
	 * @param role The role to validate (admin or reception).
	 * @return bool True if password is correct.
	 */
	bool checkPassword(const std::string& role);

	/**
	 * @brief Displays the main application menu.
	 */
	void showMainMenu();

public:
	/**
	 * @brief Constructor.
	 */
	HotelSystem(const DatabaseConfig& config);

	/** 
	 * @brief Runs the hotel management system.
	 */
	void run();
};