#include <vector>
#include <optional>
#include <stdexcept>
#include "HotelManager.h"
#include "Room.h"
#include "StandardRoom.h"
#include "DeluxeRoom.h"
#include "Suite.h"
#include "HelperFunctions.h"
// Constructors Definition
HotelManager::HotelManager(IDatabase& db):
	room_repo(db),booking_repo(db),customer_repo(db) {}

// Public Functions Definitions
void HotelManager::validateRoomExists(int room_number) const {
	room_repo.validateRoomExists(room_number);
}

void HotelManager::validateCustomerExists(int customer_id) const {
	customer_repo.validateCustomerExists(customer_id);
}

void HotelManager::validateBookingExists(int booking_id) const {
	booking_repo.validateBookingExists(booking_id);
}

bool HotelManager::isRoomAvailableForDate(int room_number, const DateTime& check_in,
	const DateTime& check_out, int exclude_booking_id) const {
	auto room = getRoomByNumber(room_number);
	if (room->getStatus() != "available")
		return false;
	auto room_bookings = booking_repo.getBookingsByRoom(room_number);
	for (const auto& other_booking : room_bookings) {
		if (exclude_booking_id == other_booking.getId())
			continue;
		if (other_booking.isOverlapping(check_in, check_out)) {
			return false;
		}
	}
	return true;
}

std::vector<std::unique_ptr<Room>> HotelManager::getAvailableRooms(const DateTime& check_in, const DateTime& check_out) const {
std::vector<bool> is_room_booked(room_repo.getNumberOfRooms() + 1, 0);
	auto all_bookings = booking_repo.getAllBookings();

	for (const auto& booking : all_bookings) {
		int room_num = booking.getRoomNumber();
		if (booking.isOverlapping(check_in, check_out)) {
			is_room_booked[room_num] = 1;
		}
	}
	std::vector<std::unique_ptr<Room>> available_rooms;

    auto all_rooms = room_repo.getAllRooms();
	for (auto& room : all_rooms) {
        int room_num = room->getNumber();
        if (is_room_booked[room_num] == 0 && room->isRoomAvailable())
			available_rooms.emplace_back(std::move(room));
    }

	return available_rooms;
}

std::unique_ptr<Room> HotelManager::getRoomByNumber(int room_num) const {
	return room_repo.getRoomByNumber(room_num);
}

Customer HotelManager::getCustomerById(int customer_id) const {
	return customer_repo.getCustomerById(customer_id);
}

Booking HotelManager::getBookingById(int booking_id) const {
	return booking_repo.getBookingById(booking_id);
}
 std::vector<std::unique_ptr<Room>> HotelManager::getRoomsByStatus(const std::string& status)const {
	return room_repo.getRoomsByStatus(status);
}
std::vector<std::unique_ptr<Room>> HotelManager::getRoomsByType(const std::string& type)const {
	return room_repo.getRoomsByType(type);
}

 std::vector<std::unique_ptr<Room>> HotelManager::getAllRooms() const {
	 return room_repo.getAllRooms();
}

std::vector<Customer> HotelManager::getAllCustomers() const {
	return customer_repo.getAllCustomers();
}

std::vector<Booking> HotelManager::getAllBookings() const {
	return booking_repo.getAllBookings();
}

void HotelManager::updateRoomPrice(int room_number, double price) {
	return room_repo.updateRoomPrice(room_number, price);
}


void HotelManager::updateRoomStatus(int room_number, const std::string& status) {
	return room_repo.updateRoomStatus(room_number, toLowerCase(status));
}

void HotelManager::updateCustomerPhone(int customer_id, const std::string& phone) {
	return customer_repo.updateCustomerPhoneNumber(customer_id, phone);
}

void HotelManager::updateCustomerEmail(int customer_id, const std::string& email) {
	validateCustomerExists(customer_id);
	return customer_repo.updateCustomerEmail(customer_id, email);
}


void HotelManager::updateBookingStatus(int booking_id, const std::string& status) {
	validateBookingExists(booking_id);
	return booking_repo.updateBookingStatus(booking_id, toLowerCase(status));
}

void HotelManager::updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out) {
	validateBookingExists(booking_id);
	return booking_repo.updateBookingDates(booking_id, check_in, check_out);
}

std::unique_ptr<Room> HotelManager::addStandardRoom(const std::string& status, double price) {

	int room_number= room_repo.addStandardRoom(StandardRoom(-1,price, status));
	return room_repo.getRoomByNumber(room_number);
}

std::unique_ptr<Room> HotelManager::addDeluxeRoom(const std::string& status, double price, double extra_fees) {
	int room_number= room_repo.addDeluxeRoom(DeluxeRoom(-1, price,status, extra_fees));
	return getRoomByNumber(room_number);
}

std::unique_ptr<Room>HotelManager::addSuite(const std::string& status, double price, bool has_jacuzzi, double jacuzzi_cost) {
	int room_number=room_repo.addSuite(Suite(-1, price, status, has_jacuzzi, jacuzzi_cost));
	return getRoomByNumber(room_number);
}

Customer HotelManager::addNewCustomer(const std::string& name, int age, const std::string& phone, const std::string& email) {
	int customer_id= customer_repo.addCustomerAndGetId(Customer(-1,name, age, phone, email));
	return getCustomerById(customer_id);
}

Booking HotelManager::addNewBooking(const DateTime& check_in, const DateTime& check_out, int customer_id, int room_number,const std::string&status) {
	validateRoomExists(room_number);
	validateCustomerExists(customer_id);
	if (!isRoomAvailableForDate(room_number, check_in, check_out, -1)) {
		throw std::runtime_error("Error: Room is not available for those dates!");
	}

	auto room = getRoomByNumber(room_number);
	int days = check_out - check_in;
	double cost = room->getTotalPrice() * days;
	int booking_id= booking_repo.addBookingAndGetId(Booking(-1, room_number, customer_id,cost , check_in, check_out,status));

	return getBookingById(booking_id);
}

void HotelManager::deleteRoom(int room_number) {
	 room_repo.deleteRoom(room_number);
}

void HotelManager::deleteCustomer(int customer_id) {
	validateCustomerExists(customer_id);
    // Check active bookings in DB instead of in-memory manager
    auto bookings = booking_repo.getAllBookings();
    for (const auto& b : bookings) {
		if (b.getCustomerId() == customer_id) {
			throw std::runtime_error("Error: Can't delete customer with active bookings!");
		}
    }
    customer_repo.deleteCustomer(customer_id);
}

void HotelManager::deleteBooking(int booking_id) {
	validateBookingExists(booking_id);
	 booking_repo.deleteBooking(booking_id);
}
