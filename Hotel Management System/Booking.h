#pragma once
#include "DateTime.h"
#include<string>

/**
  * @class Booking
  * @brief Represents a hotel booking with reservation details and scheduling information.
  *
  * This class encapsulates all the attributes and behaviors of a hotel booking,
  * including booking identification, date ranges, costs, and associated room and customer details.
  * It provides functionality to manage booking status, calculate costs based on duration,
  * check for date conflicts, and serialize booking information for storage and display.
  */
class Booking {
	int booking_id;         ///< Unique booking identifier.
	std::string status;          ///< Booking status: (Pending, Done, Cancelled).
	DateTime check_in;      ///< Check-in date and time.
	DateTime check_out;     ///< Check-out date and time.
	double cost;            ///< Total cost of the booking.
	int room_number;        ///< Room number associated with the booking.
	int customer_id;        ///< Customer identifier associated with the booking.

	/**
	 * @brief Validates if a booking status is acceptable.
	 * @Valid status values are: "pending", "done", "cancelled".
	 * @note Validation is case-insensitive.
	 * @param status The status string to validate.
	 * @return bool True if the status is valid, false otherwise.
	 */
	bool isValidStatus(std::string status)const;
	/**
	 * @brief Validates if a check-in date/time is acceptable.
	 * @details Ensures the check-in date is not in the past.
	 * @param check_in The check-in date/time to validate.
	 * @return bool True if the check-in date is valid, false otherwise.
	 */
	bool isValidCheckIn(const DateTime& check_in)const;
	/**
	 * @brief Validates if a check-out date/time is acceptable.
	 * @details Ensures the check-out date is after the check-in date and meets minimum stay requirements.
	 * @param check_out The check-out date/time to validate.
	 * @return bool True if the check-out date is valid, false otherwise.
	 */
	bool isValidCheckOut(const DateTime& check_out)const;
public:
	/**
	 * @brief Default constructor.
	 */
	Booking();

	/**
	 * @brief Parameterized constructor.
	 * @param booking_id Unique booking identifier.
	 * @param room_id Room number.
	 * @param customer_id Customer identifier.
	 * @param room_price Price per night.
	 * @param check_in Check-in date and time.
	 * @param check_out Check-out date and time.
	 * @param status Booking status.
	 */
	Booking(int booking_id, int room_id, int customer_id, double room_price,
		const DateTime& check_in, const DateTime& check_out, const std::string& status);

	/**
	 * @brief Equality comparison operator.
	 * @param rhs The other Booking to compare with.
	 * @return bool True if bookings have the same ID.
	 */
	bool operator==(const Booking& rhs) const;

	/**
	 * @brief Checks if booking overlaps with given date range.
	 * @param chin Check-in date to check.
	 * @param chout Check-out date to check.
	 * @return bool True if dates overlap.
	 */
	bool isOverlapping(const DateTime& chin, const DateTime& chout) const;

	// GETTERS AND SETTERS (kept inside - they are trivial)

	/**
	 * @brief Sets the booking status with validation.
	 * @param status_ The new status to set.
	 * @throws std::invalid_argument if the status is not valid.
	 * @note Uses isValidStatus() for validation before assignment.
	 */
	void setStatus(const std::string& status_);

	/**
	 * @brief Sets room number.
	 * @param room_num New room number.
	 */
	void setRoomNumber(int room_num) { this->room_number = room_num; }

	/**
	 * @brief Sets the check-in date with validation.
	 * @param check_in_ The new check-in date to set.
	 * @throws std::invalid_argument if the check-in date is invalid (e.g., in the past).
	 * @note Uses isValidCheckIn() for validation before assignment.
	 */
	void setCheckIn(const DateTime& check_in_);

	/**
	 * @brief Sets the check-out date with validation.
	 * @param check_out_ The new check-out date to set.
	 * @throws std::invalid_argument if the check-out date is invalid (e.g., not after check-in date).
	 * @note Uses isValidCheckOut() for validation before assignment.
	 */
	void setCheckOut(const DateTime& check_out_);

	/**
	 * @brief Gets booking ID.
	 * @return int Booking identifier.
	 */
	int getId() const { return this->booking_id; }

	/**
	 * @brief Gets booking status.
	 * @return const string& Booking status.
	 */
	const std::string& getStatus() const { return this->status; }

	/**
	 * @brief Gets booking cost.
	 * @return double Total cost.
	 */
	double getCost() const { return cost; }

	/**
	 * @brief Gets check-in date.
	 * @return const DateTime& Check-in date.
	 */
	const DateTime& getCheckIn() const { return this->check_in; }

	/**
	 * @brief Gets check-out date.
	 * @return const DateTime& Check-out date.
	 */
	const DateTime& getCheckOut() const { return this->check_out; }

	/**
	 * @brief Gets room number.
	 * @return int Room number.
	 */
	int getRoomNumber() const { return this->room_number; }

	/**
	 * @brief Gets customer ID.
	 * @return int Customer identifier.
	 */
	int getCustomerId() const { return this->customer_id; }

	// COMPLEX FUNCTIONS (declared here, defined outside)
	/**
	 * @brief Sets cost based on room price and stay duration.
	 * @param room_price Price per night.
	 */
	void setCost(double room_price);

	/**
	 * @brief Calculates number of nights.
	 * @return int Number of nights.
	 */
	int getNumberOfNights() const;

	/**
	 * @brief Serializes booking to string.
	 * details the format is:"Id,room_number,customer_id,check_in,check_out,cost,status".
	 * @return string Comma-separated booking data.
	 */
	std::string toString() const;

	/**
	 * @brief Prints booking details.
	 */
	void printBookingInfo() const;
};