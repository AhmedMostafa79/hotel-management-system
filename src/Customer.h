#pragma once

#include <string>

/**
  * @class Customer
  * @brief Represents a hotel customer with personal information and contact details.
  *
  * This class encapsulates all the attributes and behaviors of a hotel customer,
  * including their unique identifier, personal details, and contact information.
  * It provides functionality to manage customer data, serialize information for storage,
  * and display customer details in a formatted manner.
  */
class Customer {
	int id;                 ///< Customer Unique Identifier.
	int age;                ///< Customer Age.
	std::string name;            ///< Customer Name.
	std::string phone_number;    ///< Customer Phone Number (contact).
	std::string email;           ///< Customer Email (contact).
	/**
	 * @brief Validates an email address format.
	 * @details Checks if the email matches the basic pattern: local-part@domain.tld
	 * @param email_ The email address string to validate.
	 * @return bool True if the email format is valid, false otherwise.
	 */
	bool validateEmail(const std::string& email_)const;
	/**
	 * @brief Validates a phone number format.
	 * @details Checks if the phone number contains only digits and has exactly 11 characters.
	 * @param phone The phone number string to validate.
	 * @return bool True if the phone number format is valid, false otherwise.
	 */
	bool validatePhoneNumber(const std::string& phone)const;
public:
	/**
	 * @brief Default constructor
	 * @note creates an empty Customer object.
	 */
	Customer();

	/**
	 * @brief Parameterized constructor. Creates a Customer with complete information.
	 * @param id Unique identifier for the customer.
	 * @param name Full name of the customer.
	 * @param age Age of the customer.
	 * @param phone Contact phone number.
	 * @param email Contact email address.
	 */
	Customer(int id, const std::string& name, int age, const std::string& phone, const std::string& email);

	/**
	 * @brief Sets the customer's email address with validation.
	 * @param email_ The new email address to set.
	 * @throws std::invalid_argument if the email format is invalid.
	 * @note Uses validateEmail() for Validation before assignment.
	 */
	void setEmail(const std::string& email_);

	/**
	 * @brief Sets the customer's phone number with validation.
	 * @param phone_ The new phone number to set.
	 * @throws std::invalid_argument if the phone number format is invalid.
	 * @note Uses validatePhoneNumber() for Validation before assignment.
	 */
	void setPhoneNumber(const std::string& phone);

	/**
	 * @brief Gets customer's unique identifier(ID).
	 * @return int The customer ID.
	 */
	int getId() const { return id; }

	/**
	 * @brief Gets customer's name.
	* @return const string& Constant reference to the name string.
	 */
	const std::string& getName() const { return name; }

	/**
	 * @brief Gets customer's age.
	 * @return int The customer age.
	 */
	int getAge() const { return age; }

	/**
	 * @brief Gets customer's email.
	* @return const string& Constant reference to the email string.
	 */
	const std::string& getEmail() const { return email; }

	/**
	 * @brief Gets customer's phone number.
	* @return const string& Constant reference to the phone number string.
	 */
	const std::string& getPhoneNumber() const { return phone_number; }

	/**
	 * @brief Equality comparison operator.
	 * @param other The other Customer to compare with.
	 * @return bool True if customers have the same ID.
	 */
	bool operator==(const Customer& other) const;

	/**
	 * @brief Serializes the Customer object to a string representation.
	 * @details Format: "id,name,age,phone_number,email".
	* @return string Comma-separated values containing customer's data.
	 */
	std::string toString() const;

	/**
	 * @brief Prints the customer's information to standard output in a formatted way.
	 * @details the output is indented and formatted for console display.
	 */
	void printCustomerInfo() const;
};
