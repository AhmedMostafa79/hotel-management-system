#include<string>
#include<iostream>
#include<regex>
#include <sstream>    
#include <stdexcept> 
#include <cctype>     
#include "Customer.h"
// Constructors Definition
Customer::Customer() : id(0), age(0), name(""), phone_number(""), email("") {}

Customer::Customer(int id, const std::string& name, int age, const std::string& phone, const std::string& email)
	: id(id), age(age), name(name) {
	setEmail(email);
	setPhoneNumber(phone);
}
//Private Function Definitions 
bool Customer::validateEmail(const std::string& email_)const {
	const std::regex pattern(R"(\w+@\w+\.\w+)");
	return std::regex_match(email_, pattern);
}
bool Customer::validatePhoneNumber(const std::string& phone)const {
	for (const auto& i : phone) {
		if (!std::isdigit(static_cast<unsigned char>(i)))
			return false;
	}
	return phone.size() == 11;
}

// Public FUNCTION DEFINITIONS
void  Customer::setPhoneNumber(const std::string& phone_) {
	if (validatePhoneNumber(phone_)) {
		phone_number = phone_;
	}
	else {
		throw std::invalid_argument("Error!  Invalid phone number.");
	}
}
void Customer::setEmail(const std::string& email_) {
	if (validateEmail(email_))
		this->email = email_;
	else {
		throw std::invalid_argument("Error!  Invalid email format.");
	}
}
bool Customer::operator==(const Customer& other) const {
	return getId() == other.getId();
}

std::string Customer::toString() const {
	std::ostringstream ss;
	ss << std::to_string(id) << "," << name << "," << std::to_string(age) << "," << phone_number << "," << email;
	return ss.str();
}

void Customer::printCustomerInfo() const {
	std::cout << "\t\t\tName: " << getName() << "\n";
	std::cout << "\t\t\tID: " << getId() << '\n';
	std::cout << "\t\t\tAge: " << getAge() << '\n';
	std::cout << "\t\t\tPhone Number: " << getPhoneNumber() << '\n';
	std::cout << "\t\t\tEmail: " << getEmail() << '\n';
	std::cout << "\n";
}