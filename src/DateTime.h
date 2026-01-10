#pragma once

#include<string>
#include<chrono>
/**
  * @class DateTime
  * @brief Represents a specific point in time with comprehensive formatting capabilities.
  * using the chrono library for internal storage and supporting string conversion
  * in standard ISO-like formats. It features cross-platform thread-safe implementation
*/

class DateTime {
private:
	std::chrono::system_clock::time_point m_time;

public:
	/**
	 * @brief Default constructor.
	 * @details Initializes the DateTime object to current system time.
	 */
	DateTime();

	/**
	 * @brief Constructor from formatted string.
	 * @param dateTimeString String in "YYYY-MM-DD HH:MM:SS" format.
	 * @throw std::invalid_argument If the input string format is incorrect.
	 */
	DateTime(const std::string& dateTimeString);

	/**
	 * @brief Adds specified number of days to the DateTime.
	 * @param days Number of days to add.
	 * @return DateTime New DateTime object with added days.
	 */
	DateTime operator+(int days) const;

	/**
	 * @brief Calculates the difference in days between two DateTime objects.
	 * @param other The DateTime to subtract from this DateTime.
	 * @return int Number of days between this DateTime and the other DateTime.
	 */
	int operator-(const DateTime& other) const;

	/**
	 * @brief Less than or equal comparison.
	 * @param rhs DateTime to compare against.
	 * @return bool True if this DateTime <= rhs.
	 */
	bool operator<=(const DateTime& rhs) const;

	/**
	 * @brief Greater than or equal comparison.
	 * @param rhs DateTime to compare against.
	 * @return bool True if this DateTime >= rhs.
	 */
	bool operator>=(const DateTime& rhs) const;

	/**
	 * @brief Greater than comparison.
	 * @param rhs DateTime to compare against.
	 * @return bool True if this DateTime > rhs.
	 */
	bool operator>(const DateTime& rhs) const;

	/**
	 * @brief Less than comparison.
	 * @param rhs DateTime to compare against.
	 * @return bool True if this DateTime < rhs.
	 */
	bool operator<(const DateTime& rhs) const;

	/**
	 * @brief Sets time from time_point object.
	 * @param new_time The new time point to set.
	 */
	void setDateTime(const std::chrono::system_clock::time_point& new_time);

	/**
	 * @brief Sets time by parsing formatted string.
	 * @param date_time_string String in "YYYY-MM-DD HH:MM:SS" format.
	 * @throw std::invalid_argument If the input string format is incorrect.
	 */
	void setDateTime(const std::string& date_time_string);

	/**
	 * @brief Sets the time to 12:00:00 PM (noon) while keeping the same date.
	 * The date portion remains unchanged from the current m_time value.
	 */
	void setDateAtNoon();

	/**
	 * @brief Converts to standardized string representation.
	 * @return string Formatted as "YYYY-MM-DD HH:MM:SS".
	 */
	std::string getDateTimeString() const;

	/**
	 * @brief Extracts time portion of the DateTime.
	 * @return string Formatted as "HH:MM:SS".
	 */
	std::string getTimeString() const;

	/**
	 * @brief Extracts date portion of the DateTime.
	 * @return string Formatted as "YYYY-MM-DD".
	 */
	std::string getDateString() const;

	/**
	 * @brief Gets internal time_point representation.
	 * @return chrono::system_clock::time_point Underlying time point.
	 */
	std::chrono::system_clock::time_point getTimePoint() const;
};