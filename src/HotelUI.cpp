#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include "HotelUI.h"
#include "HelperFunctions.h"
// Private Functions Definition
HotelManager& HotelUI::getHotelManager() {
	return hotel_manager;
}
const HotelManager& HotelUI::getHotelManager()const {
	return hotel_manager;
}
void HotelUI::printRooms(const std::vector<std::unique_ptr<Room>>& rooms)const {
	for (const auto& room : rooms) {
		room->printRoomInfo();
	}
}

// Constructors Definitions
HotelUI::HotelUI(HotelManager& manager) : hotel_manager(manager) {}

// Public Functions Definition
void HotelUI::printAvailableRoomsUI(const DateTime& chin, const DateTime& chout) const {
	auto available_rooms = getHotelManager().getAvailableRooms(chin, chout);
	std::cout << "\n\t\t=== Available Rooms ===\n";

	for (const auto& room : available_rooms) {
		room->printRoomInfo();
	}
	std::cout << '\n';
}
void HotelUI::printRoomsByStatusUI()const {
	std::vector<std::string>room_statuses = { "Available","Maintenance","Previous Menu" };
	int  status_num = showInnerReadMenu("Enter room status", room_statuses);
	if (status_num == 3)
		return;
	std::string status = toLowerCase(room_statuses[status_num - 1]);
	auto rooms = getHotelManager().getRoomsByStatus(status);
	printRooms(rooms);
}

void HotelUI::printRoomsByTypeUI()const {
	std::vector<std::string>room_types = { "Standard","Deluxe","Suite","Previous Menu" };
	int  type_num = showInnerReadMenu("Enter room type", room_types);
	if (type_num == 4)
		return;
	std::string type = toLowerCase(room_types[type_num - 1]);
	auto rooms = getHotelManager().getRoomsByType(type);
	printRooms(rooms);
}

void HotelUI::printAllRoomsUI() const {
	std::cout << "\n\t\t=== All Rooms ===\n\n";

	auto rooms = getHotelManager().getAllRooms();
	printRooms(rooms);
}

void HotelUI::printAllCustomersUI() const {
	std::cout << "\n\t\t=== All Customers ===\n\n";

	auto customers = getHotelManager().getAllCustomers();
	for (const auto& customer : customers) {
		customer.printCustomerInfo();
	}
}

void HotelUI::printAllBookingsUI() const {
	std::cout << "\n\t\t=== All Bookings ===\n\n";

	auto bookings = getHotelManager().getAllBookings();
	for (const auto& booking : bookings) {
		booking.printBookingInfo();
	}
}

void HotelUI::printRoomByNumberUI() const {
	int room_number = getValidatedInt("\t\tEnter Room number: ");
	try {
		auto room = getHotelManager().getRoomByNumber(room_number);
		std::cout << "\n\t\t=== Room Details ===\n";
		room->printRoomInfo();
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::printCustomerByIdUI() const {
	int customer_id = getValidatedInt("\t\tEnter Customer ID: ");
	try {
		auto customer = getHotelManager().getCustomerById(customer_id);
		std::cout << "\n\t\t=== Customer Details ===\n";
		customer.printCustomerInfo();
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::printBookingByIDUI() const {
	int booking_id = getValidatedInt("\t\tEnter Booking ID: ");
	try {
		auto booking = getHotelManager().getBookingById(booking_id);
		std::cout << "\n\t\t=== Booking Details ===\n\n";
		booking.printBookingInfo();
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}


std::unique_ptr<Room> HotelUI::readStandardRoomUI(const std::string& status, double price) {
	return getHotelManager().addStandardRoom(status, price);
}
std::unique_ptr<Room> HotelUI::readDeluxeRoomUI(const std::string& status, double price) {
	std::cout << "\t\t=== Read Deluxe Room ===\n\n";
	double fees = getValidatedDouble("\t\t\tEnter Fees: ");
	return  getHotelManager().addDeluxeRoom(status, price, fees);
}
std::unique_ptr<Room>  HotelUI::readSuiteUI(const std::string& status, double price) {
	std::cout << "\t\t=== Read Suite ===\n\n";
	int has_jac = showInnerReadMenu("Does suite has Jacuzzi?", { "Has Jacuzzi","Doesn't has Jacuzzi" });
	double jac_cost = 0;
	if (has_jac == 1)
		jac_cost = getValidatedInt("\t\t\tEnter Jacuzzi Cost: ");
	return  getHotelManager().addSuite(status, price, has_jac==1?1:0, jac_cost);
}


void HotelUI::addNewRoomUI() {
	std::cout << "\t\t*** Add New Room ***\n\n";

	std::vector<std::string>room_types = { "Standard","Deluxe","Suite","Previous Menu" };
	int  type = showInnerReadMenu("Enter room type", room_types);
	if (type == 4) return;

	std::vector<std::string>room_statuses = { "Available","Maintenance" };
	int  status_num = showInnerReadMenu("Enter room status", room_statuses);
	std::string status = toLowerCase(room_statuses[status_num - 1]);

	double price = getValidatedDouble("\t\t\tEnter Price: ");
	try {
		std::unique_ptr<Room> added_room = nullptr;

		switch (type) {
		case 1: added_room = readStandardRoomUI(status, price); break;
		case 2:    added_room = readDeluxeRoomUI(status, price); break;
		case 3:added_room = readSuiteUI(status, price); break;
		}
		std::cout << "\n\t\tRoom is added successfully!\n\n";
		std::cout << "\t\tRoom Details:\n";
		added_room->printRoomInfo();
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::addNewCustomerUI() {
	std::cout << "\t\t*** Add New Customer ***\n\n";
	std::string name;

	std::cout << "\t\t\tEnter customer name: ";
	std::cin >> name;

	int age = getValidatedInt("\t\t\tEnter age: ");

	std::string phone_number;
	std::cout << "\t\t\tEnter phone number: ";
	std::cin >> phone_number;

	std::string email;
	std::cout << "\t\t\tEnter email: ";
	std::cin >> email;

	try {
		auto new_customer = getHotelManager().addNewCustomer(name, age, phone_number, email);
			std::cout << "\n\t\tCustomer is added successfully!\n\n";
			std::cout << "\t\tCustomer Details:\n";
			new_customer.printCustomerInfo();
	}

	catch (const std::exception& e) {
		std::cout << "\n\t\t"<< e.what() << "\n\n";
	}

}

void HotelUI::addNewBookingUI() {
	std::cout << "\t\t*** Add New Booking ***\n\n";

	std::string date;
	std::cout << "\n\t\t\tEnter Check-In date(YYYY-MM-DD): ";
	std::cin >> date;

	int days = getValidatedInt("\t\t\tEnter number of staying days: ");

	int  customer_id = getValidatedInt("\n\t\t\tEnter Customer Id: ");

	DateTime check_in(date);
	check_in.setDateAtNoon();
	DateTime check_out(check_in + days);

	printAvailableRoomsUI(check_in, check_out);
	int room_number = getValidatedInt("\n\t\t\tEnter room number: ");

	try {
		std::string default_status = "pending";
		auto new_booking = getHotelManager().addNewBooking(check_in, check_out, customer_id, room_number, default_status);
	std::cout << "\n\t\tBooking is added successfully!\n\n";
	std::cout << "\t\tBooking Details:\n";
		new_booking.printBookingInfo();
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}
void HotelUI::deleteRoomUI() {
	int room_number = getValidatedInt("\t\t\tEnter room number: ");
	try {
		getHotelManager().deleteRoom(room_number);
		std::cout << "\n\t\tRoom is deleted successfully\n\n";
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::deleteCustomerUI() {
	int customer_id = getValidatedInt("\n\t\tEnter customer ID: ");

	try {
		getHotelManager().deleteCustomer(customer_id);
		std::cout << "\n\t\tCustomer is deleted successfully\n\n";
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::deleteBookingUI() {
	int booking_id = getValidatedInt("\n\t\tEnter booking number: ");

	try {
		getHotelManager().deleteBooking(booking_id);
		std::cout << "\n\t\tBooking is deleted successfully\n\n";
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::modifyRoomUI() {
	int room_number = getValidatedInt("\t\t\tEnter Room Number: ");

	try {
		getHotelManager().validateRoomExists(room_number);

		std::vector<std::string>available_choices = { "Change base price","Change room status","Finish updating" };
		std::string menu_name = "Room Update Menu";

		int choice = 0;
		do {

			choice = showInnerReadMenu(menu_name, available_choices);
			try {
				if (choice == 1) {
					double price = getValidatedDouble("\t\t\tEnter price per night: ");
					getHotelManager().updateRoomPrice(room_number, price);
				}
				else if (choice == 2) {
					std::vector<std::string>room_statuses = { "Available","Maintenance" };
					int  status_num = showInnerReadMenu("Enter room status", room_statuses);
					std::string status = room_statuses[status_num - 1];
					getHotelManager().updateRoomStatus(room_number, status);
					std::cout << "\n\t\tStatus updated successfully!\n";
				}
			}
			catch (const std::exception& e) {
				std::cout << "\n\t\t" << e.what() << "\n\n";
			}
		} while (choice != 3);
	std::cout << "\n\t\tRoom details after update:\n";
		auto updated_room = getHotelManager().getRoomByNumber(room_number);
		updated_room->printRoomInfo();
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::modifyCustomerUI() {
	int customer_id = getValidatedInt("\t\t\tEnter Customer ID: ");

	try {
		getHotelManager().validateCustomerExists(customer_id);

	std::vector<std::string>available_choices = { "Change Phone number","Change Email","Finish Updating" };
	std::string menu_name = "Customer Update Menu";

		int choice = 0;
		do {
			choice = showInnerReadMenu(menu_name, available_choices);
			try {
				if (choice == 1) {
					std::string phone;
					std::cout << "\t\t\tEnter Phone number: ";
					std::cin >> phone;
					getHotelManager().updateCustomerPhone(customer_id, phone);
					std::cout << "\n\t\tPhone Number updated successfully!\n";

				}
				else if (choice == 2) {
					std::string email;
					std::cout << "\t\t\tEnter Email: ";
					std::cin >> email;
					getHotelManager().updateCustomerEmail(customer_id, email);
					std::cout << "\n\t\tEmail updated successfully!\n";
				}
			}
			catch (const  std::exception& e) {
				std::cout << "\n\t\t" << e.what() << "\n\n";
			}

		} while (choice != 3);
		auto customer = getHotelManager().getCustomerById(customer_id);
	std::cout << "\n\t\tCustomer  data after update:\n\n";
	customer.printCustomerInfo();
	std::cout << '\n';
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}

void HotelUI::modifyBookingUI() {
	int booking_id = getValidatedInt("\t\t\tEnter Booking ID: ");
	try {
		auto booking = getHotelManager().getBookingById(booking_id);
	std::vector<std::string>available_choices = { "Change Status","Change Check-In/Out" ,"Finish Updating" };
	std::string menu_name = "Booking Update Menu";
		int choice = 0;
		do {
			choice = showInnerReadMenu(menu_name, available_choices);
			try {
				if (choice == 1) {
					std::vector<std::string>booking_statuses = { "Pending","Done" };
					int  status_num = showInnerReadMenu("Enter room status", booking_statuses);
					std::string status = toLowerCase(booking_statuses[status_num - 1]);
					getHotelManager().updateBookingStatus(booking_id, status);
					std::cout << "\n\t\tStatus changed successfully!\n";

				}
				else if (choice == 2) {
					std::string date;
					std::cout << "\t\t\tEnter Check-In date(YYYY-MM-DD): ";
					std::cin >> date;
					int days = getValidatedInt("\t\t\tEnter number of staying days: ");

					DateTime check_in(date);
					DateTime check_out = check_in + days;
					int room_number = booking.getRoomNumber();
					auto room = getHotelManager().getRoomByNumber(room_number);
					getHotelManager().updateBookingDates(booking_id, check_in, check_out);
					std::cout << "\n\t\tCheck-In/Out changed successfully\n";
				}
			}
			catch (const std::exception& e) {
				std::cout << "\n\t\t" << e.what() << "\n\n";
			}
		} while (choice != 3);
		auto booking_after_update = getHotelManager().getBookingById(booking_id);
	std::cout << "\n\t\tBooking Details after update:\n\n";
	booking_after_update.printBookingInfo();
	std::cout << '\n';
	}
	catch (const std::exception& e) {
		std::cout << "\n\t\t" << e.what() << "\n\n";
	}
}