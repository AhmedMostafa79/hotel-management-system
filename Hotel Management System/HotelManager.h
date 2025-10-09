#pragma once

#include"Room.h"
#include "Customer.h"
#include "Booking.h"
#include "RoomRepository.h"
#include "CustomerRepository.h"
#include "BookingRepository.h"
#include "IDatabase.h"
#include <vector>
#include <optional>
#include <memory>
/**
	* @class HotelManager
	* @brief Central management class that coordinates all hotel operations and subsystems.
	* This class serves as the main facade for the hotel management system,
	* providing a unified interface to manage rooms, customers, and bookings.
	* It orchestrates the interactions between RoomsManager, CustomersManager,
	* and BookingsManager, ensuring data consistency and business rule enforcement
	* across all hotel operations including availability checks, booking conflicts,
	* and customer-room relationships.
	*/
class HotelManager {
	RoomRepository room_repo;
	BookingRepository booking_repo;
	CustomerRepository  customer_repo;
    
public:
	/**
	 * @brief Default constructor.
	 */
	HotelManager(IDatabase&db);

	/**
	 * @brief Validates that a room exists.
	 * @param room_number The room number to validate.
	 * @return bool True if room exists.
	 * @throws invalid_argument If room doesn't exist.
	 */
	void validateRoomExists(int room_number) const;

	/**
	 * @brief Validates that a customer exists.
	 * @param customer_id The customer ID to validate.
	 * @return bool True if customer exists.
	 * @throws invalid_argument If customer doesn't exist.
	 */
	void validateCustomerExists(int customer_id) const;

	/**
	 * @brief Validates that a booking exists.
	 * @param booking_id The booking ID to validate.
	 * @return bool True if booking exists.
	 * @throws invalid_argument If booking doesn't exist.
	 */
	void validateBookingExists(int booking_id) const;

	/**
	 * @brief Checks if a room is available for given dates.
	 * @param room_number The room number to check.
	 * @param check_in Check-in date.
	 * @param check_out Check-out date.
	 * @param exclude_booking_id Booking ID to exclude from conflict check.
	 * @return bool True if room is available.
	 */
	bool isRoomAvailableForDate(int room_number, const DateTime& check_in,
		const DateTime& check_out, int exclude_booking_id) const;

	/**
	 * @brief Gets all available rooms for given dates.
	 * @param check_in Check-in date.
	 * @param check_out Check-out date.
	 * @return vector<Room> List of available rooms.
	 */
	std::vector<std::unique_ptr<Room>> getAvailableRooms(const DateTime& check_in, const DateTime& check_out) const;

	/**
	 * @brief Gets a room by its number.
	 * @param room_num The room number.
	 * @return optional<Room> The room if found.
	 */
	std::unique_ptr<Room> getRoomByNumber(int room_num) const;

	/**
	 * @brief Gets a customer by their ID.
	 * @param customer_id The customer ID.
	 * @return optional<Customer> The customer if found.
	 */
	Customer getCustomerById(int customer_id) const;

	/**
	 * @brief Gets a booking by its ID.
	 * @param booking_id The booking ID.
	 * @return optional<Booking> The booking if found.
	 */
	Booking getBookingById(int booking_id) const;

	/**
	 * @brief Retrieves read-only rooms filtered by their current status.
	 * @details Delegates to the RoomsManager to get rooms with the specified status.
	 * @param status The status to filter by (e.g., "Available", "Maintenance").
	 * @return const vector<const Room*> A vector of constant pointers to rooms matching the status.
	 */
	std::vector<std::unique_ptr<Room>> getRoomsByStatus(const std::string& status)const;
	/**
	 * @brief Retrieves read-only rooms filtered by their type.
	 * @details Delegates to the RoomsManager to get rooms of the specified type.
	 * @param type The room type to filter by (e.g., "standard", "deluxe", "suite").
	 * @return const vector<const Room*> A vector of constant pointers to rooms matching the type.
	 */
	std::vector<std::unique_ptr<Room>> getRoomsByType(const std::string& type)const;
	/**
	 * @brief Gets all rooms.
	 * @return vector<const Room*> List of all rooms.
	 */
	std::vector<std::unique_ptr<Room>> getAllRooms() const;

	/**
	 * @brief Gets all customers.
	 * @return vector<const Customer*> List of all customers.
	 */
	std::vector<Customer> getAllCustomers() const;

	/**
	 * @brief Gets all bookings.
	 * @return vector<const Booking*> List of all bookings.
	 */
	std::vector<Booking> getAllBookings() const;

	/**
	 * @brief Updates room price.
	 * @param room_number Room number.
	 * @param price New price.
	 * @return bool True if update successful.
	 */
	void updateRoomPrice(int room_number, double price);


	/**
	 * @brief Updates room status.
	 * @param room_number Room number.
	 * @param status New room status.
	 * @return bool True if update successful.
	 */
	void updateRoomStatus(int room_number, const std::string& status);

	/**
	 * @brief Updates customer phone number.
	 * @param customer_id Customer ID.
	 * @param phone New phone number.
	 * @return bool True if update successful.
	 */
	void updateCustomerPhone(int customer_id, const std::string& phone);

	/**
	 * @brief Updates customer email.
	 * @param customer_id Customer ID.
	 * @param email New email address.
	 * @return bool True if update successful.
	 */
	void updateCustomerEmail(int customer_id, const std::string& email);

	/**
	 * @brief Updates booking status.
	 * @param booking_id Booking ID.
	 * @param status New booking status.
	 * @return bool True if update successful.
	 */
	void updateBookingStatus(int booking_id, const std::string& status);

	/**
	 * @brief Updates booking dates.
	 * @param booking_id Booking ID.
	 * @param check_in New check-in date.
	 * @param check_out New check-out date.
	 * @return bool True if update successful.
	 */
	void updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out);

	/**
	 * @brief Adds a standard room to hotel inventory.
	 * @details Delegates room creation to RoomsManager.
	 * @param status Initial room status.
	 * @param price Base price per night.
	 * @return read-only Room pointer if successful, nullopt otherwise.
	 */
	std::unique_ptr<Room> addStandardRoom(const std::string& status, double price);

	/**
	 * @brief Adds a deluxe room to hotel inventory.
	 * @details Delegates room creation to RoomsManager.
	 * @param status Initial room status.
	 * @param price Base price per night.
	 * @param extra_fees Additional premium amenities fees.
	 * @return a read-only Room pointer if successful, nullopt otherwise.
	 */
	std::unique_ptr<Room> addDeluxeRoom(const std::string& status, double price, double extra_fees);

	/**
	 * @brief Adds a suite to hotel inventory.
	 * @details Delegates room creation to RoomsManager.
	 * @param status Initial room status.
	 * @param price Base price per night.
	 * @param has_jacuzzi Whether suite has jacuzzi.
	 * @param jacuzzi_cost Additional jacuzzi cost.
	 * @return read-only Room pointer if successful, nullopt otherwise.
	 */
	std::unique_ptr<Room> addSuite(const std::string& status, double price, bool has_jacuzzi, double jacuzzi_cost);
	/**
	 * @brief Adds a new customer.
	 * @param name Customer name.
	 * @param age Customer age.
	 * @param phone Customer phone number.
	 * @param email Customer email address.
	 * @return optional<Customer> The created customer if successful.
	 */
	Customer addNewCustomer(const std::string& name, int age, const std::string& phone, const std::string& email);

	/**
	 * @brief Adds a new booking.
	 * @param date Booking date string.
	 * @param days Number of days to stay.
	 * @param customer_id Customer ID.
	 * @param room_number Room number.
	 * @return optional<Booking> The created booking if successful.
	 */
	Booking addNewBooking(const DateTime& check_in, const DateTime& check_out, int customer_id, int room_number, const std::string& status);

	/**
	 * @brief Deletes a room from the system.
	 * @param room_number Room number to delete.
	 * @return bool True if deletion successful.
	 */
	void deleteRoom(int room_number);

	/**
	 * @brief Deletes a customer from the system.
	 * @param customer_id The ID of the customer to delete.
	 * @return bool True if deletion was successful.
	 * @throws runtime_error If customer has active bookings.
	 */
	void deleteCustomer(int customer_id);

	/**
	 * @brief Deletes a booking from the system.
	 * @param booking_id The ID of the booking to delete.
	 * @return bool True if deletion was successful.
	 */
	void deleteBooking(int booking_id);

	// Prevents any assignment for manager
	HotelManager(const HotelManager&) = delete;
	HotelManager& operator=(const HotelManager&) = delete;
};