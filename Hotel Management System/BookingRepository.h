#pragma once

#include "IDatabase.h"
#include "Booking.h"
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * @file BookingRepository.h
 * @brief Persistence operations for Booking entities.
 * 
 * The BookingRepository implements CRUD operations for Booking objects using the
 * provided IDatabase adapter. All methods operate on the underlying
 * database and translate rows into concrete Booking object.
 */
class BookingRepository {
	IDatabase& database; ///< Database adapter reference used to run queries.

	/**
	 * @brief Construct a Booking object from a result row.
	 * @param result Result row to read booking fields from.
	 * @return Booking Constructed Booking value.
	 */
	Booking createBookingFromRow(const IGenericResultSet& result) const;

	/**
	 * @brief Convert a result set into a vector of Booking objects.
	 * @param result Owned result set returned from a query.
	 * @return std::vector<Booking> List of bookings.
	 */
	std::vector<Booking> fetchBookings(std::unique_ptr<IGenericResultSet> result) const;

	/**
	 * @brief Read the last auto-increment id produced by an insert.
	 * @return int Last inserted id.
	 */
	int getLastInsertedId() const;

public:
	/**
	 * @brief Construct a BookingRepository using the given database adapter.
	 * @param db Database adapter to use for queries.
	 */
	BookingRepository(IDatabase& db);

	/**
	 * @brief Check whether a booking exists by id.
	 * @param booking_id Booking identifier to check.
	 * @return true if booking exists, false otherwise.
	 */
	bool doesBookingExist(int booking_id) const;

	/**
	 * @brief Validate that a booking exists; throw if not present.
	 * @param booking_id Booking id to validate.
	 * @throws std::invalid_argument if the booking does not exist.
	 */
	void validateBookingExists(int booking_id) const;

	// CREATE
	/**
	 * @brief Insert a booking record and return the new id.
	 * @param booking Booking value to persist.
	 * @return int New booking id.
	 */
	int addBookingAndGetId(const Booking& booking);

	// READ
	/**
	 * @brief Load a booking by id.
	 * @param booking_id Booking id to load.
	 * @return Booking Loaded booking value.
	 */
	Booking getBookingById(int booking_id) const;

	/**
	 * @brief Get total number of bookings stored.
	 * @return int Number of bookings.
	 */
	int getNumberOfBookings() const;

	/**
	 * @brief Retrieve all bookings.
	 * @return std::vector<Booking> All bookings.
	 */
	std::vector<Booking> getAllBookings() const;

	/**
	 * @brief Get bookings associated with a particular room.
	 * @param room_num Room number to filter bookings.
	 * @return std::vector<Booking> Bookings for the room.
	 */
	std::vector<Booking> getBookingsByRoom(int room_num) const;

	// UPDATE
	/**
	 * @brief Change the status of a booking.
	 * @param booking_id Booking id to update.
	 * @param status New status string.
	 */
	void updateBookingStatus(int booking_id, const std::string& status);

	/**
	 * @brief Update the check-in/check-out dates for a booking.
	 * @param booking_id Booking id to update.
	 * @param check_in New check-in date.
	 * @param check_out New check-out date.
	 */
	void updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out);

	// DELETE
	/**
	 * @brief Remove a booking by id.
	 * @param booking_id Booking id to delete.
	 */
	void deleteBooking(int booking_id);
};