#include <vector>
#include <string>
#include <iostream>
#include "HotelSystem.h"
#include "HelperFunctions.h"
#include "MySQLDatabase.h"
// Private Functions Definition
HotelUI& HotelSystem::getHotelUI() {
	return hotel_ui;
}

HotelManager& HotelSystem::getHotelManager() {
	return hotel_manager;
}

void HotelSystem::showAdminRoomManagement() {
	std::vector<std::string> menu_items = {
		"Add New Room",
		"Delete Room",
		"Modify Room Details",
		"View Room Details",
		"View All Rooms",
		"Back to previous Menu"
	};

	while (true) {
		int choice = showInnerReadMenu("ROOMS MANAGEMENT", menu_items);
		switch (choice) {
		case 1: getHotelUI().addNewRoomUI(); break;
		case 2: getHotelUI().deleteRoomUI(); break;
		case 3: getHotelUI().modifyRoomUI(); break;
		case 4: getHotelUI().printRoomByNumberUI(); break;
		case 5: getHotelUI().printAllRoomsUI(); break;
		case 6:return;
		}
	}
}

void HotelSystem::showReceptionistRoomOperations() {
	std::vector<std::string> menu_items = {
		"View All Rooms",
		"View a Room",
		"View  Available Rooms",
		"View Rooms By Status",
		"View Rooms By Type",
		"Back to previouse Menu"
	};

	while (true) {
		int choice = showInnerReadMenu("ROOM INFORMATION", menu_items);

		switch (choice) {
		case 1:
			getHotelUI().printAllRoomsUI();
			break;

		case 2:
			getHotelUI().printRoomByNumberUI();
			break;

		case 3: {
			std::string date;
			std::cout << "\t\tEnter check-in date (YYYY-MM-DD): ";
			std::cin >> date;
			int days = getValidatedInt("\t\tEnter number of staying days:");
			DateTime check_in(date);
			DateTime check_out(check_in + days);
			getHotelUI().printAvailableRoomsUI(check_in, check_out);
			break;
		}
		case 4:
			getHotelUI().printRoomsByStatusUI(); break;
		case 5:
			getHotelUI().printRoomsByTypeUI(); break;
		case 6:
			return;
		}
	}
}

void HotelSystem::showCustomerManagementMenu() {
	std::vector<std::string> menu_items = {
		"Add New Customer",
		"Delete Customer",
		"Update Customer Information",
		"View Customer Details",
		"View All Customer",
		"Back to previouse Menu"
	};

	while (true) {
		int choice = showInnerReadMenu("CUSTOMERS MANAGEMENT", menu_items);

		switch (choice) {
		case 1: getHotelUI().addNewCustomerUI(); break;
		case 2: getHotelUI().deleteCustomerUI(); break;
		case 3: getHotelUI().modifyCustomerUI(); break;
		case 4: getHotelUI().printCustomerByIdUI(); break;
		case 5: getHotelUI().printAllCustomersUI(); break;
		case 6: return;
		}
	}
}

void HotelSystem::showBookingManagementMenu() {
	std::vector<std::string> menu_items = {
		"Create Booking",
		"Cancel Booking",
		"Modify Booking",
		"View Booking Details",
		"View All Bookings",
		"Back to previouse Menu"
	};

	while (true) {
		int choice = showInnerReadMenu("BOOKINGS MANAGEMENT", menu_items);
		switch (choice) {
		case 1: getHotelUI().addNewBookingUI(); break;
		case 2: getHotelUI().deleteBookingUI(); break;
		case 3: getHotelUI().modifyBookingUI(); break;
		case 4: getHotelUI().printBookingByIDUI(); break;
		case 5: getHotelUI().printAllBookingsUI(); break;
		case 6: return;
		}
	}
}

void HotelSystem::showAdminMenu() {
	std::vector<std::string> menu_items = {
		"Rooms Management",
		"Back to Main Menu" };
	while (true) {
		int choice = showOuterReadMenu("ADMIN MENU", menu_items);
		switch (choice) {
		case 1:showAdminRoomManagement(); break;
		case 2:return;
		}
	}
}

void HotelSystem::showReceptionistMenu() {
	std::vector<std::string> menu_items = {
		"Bookings Management",
		"Customers Management",
		"Rooms Information",
		"Back to Main Menu" };
	while (true) {
		int choice = showOuterReadMenu("RECEPTIONIST MENU", menu_items);
		switch (choice) {
		case 1:showBookingManagementMenu(); break;
		case 2:showCustomerManagementMenu(); break;
		case 3:showReceptionistRoomOperations(); break;
		case 4:return;
		}
	}
}
bool HotelSystem::isAdmin(const std::string& role)const {
	return role == "admin";
}
bool HotelSystem::checkPassword(const std::string& role) {
	std::string password;
	std::cout << "\n\t\tEnter " << role << " password: ";
	std::cin >> password;
	if (isAdmin(role))
		return password == "admin";
	else
		return password == "reception";
}
void HotelSystem::showMainMenu() {
	std::vector<std::string> menu_items = {
		"View Admin Menu",
		"View Receptionist Menu",
		"Exit" };
	while (true) {
		int choice = showOuterReadMenu("MAIN MENU", menu_items);
		switch (choice) {
		case 1:
			if (checkPassword("admin")) {
				showAdminMenu();
			}
			else {
				std::cout << "\n\t\tInvalid admin password!\n";
			}
			break;
		case 2:
			if (checkPassword("reception"))
				showReceptionistMenu();
			else
				std::cout << "\n\t\tInvalid receptionist password!\n";
			break;
		case 3:
			std::cout << "\n\t\tThank you for using the system!\n";
			return;
		}
	}
}

//Constructors Definition
HotelSystem::HotelSystem(const DatabaseConfig&config) :database(),hotel_manager(database), hotel_ui(hotel_manager) {
	database.connect(config);
}
// Public Functions Definition
void HotelSystem::run() {
	showMainMenu();
}