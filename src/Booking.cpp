#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include "DateTime.h"
#include <iostream>
#include "Booking.h"
// Constructors Definition
Booking::Booking() : booking_id(-1), cost(0), room_number(0), customer_id(0), status("") {}

Booking::Booking(int booking_id, int room_id, int customer_id, double cost_,
	const DateTime& check_in, const DateTime& check_out, const std::string& status)
	: booking_id(booking_id), room_number(room_id), customer_id(customer_id),cost(cost_)
{
	setStatus(status);
	setCheckIn(check_in);
	setCheckOut(check_out);
}
//Private Functions Definition

bool Booking::isValidStatus(std::string status)const {
	for (auto& i : status)
		i = static_cast<char>(std::tolower(static_cast<unsigned char>(i)));
	return status == "pending" or status == "done" or status == "cancelled";
}
bool Booking::isValidCheckIn(const DateTime& check_in)const {
	auto temp = check_in;
	temp.setDateAtNoon();
	return  check_in >= temp;
}
bool Booking::isValidCheckOut(const DateTime& check_out)const {
	return this->check_in < check_out;
}

// Public Function Definitions
bool Booking::operator==(const Booking& rhs) const {
	return getId() == rhs.getId();
}

bool Booking::isOverlapping(const DateTime& chin, const DateTime& chout) const {
	return !((chout <= check_in) || (check_out <= chin));
}

void Booking::setStatus(const std::string& status_) {
	if (isValidStatus(status_)) {
		status = status_;
	}
	else {
		throw std::invalid_argument("Error: Invalid status.");
	}
}
void Booking::setCheckIn(const DateTime& check_in_) {
	if (isValidCheckIn(check_in_))
		this->check_in = check_in_;
	else {
		throw std::invalid_argument("Error: Check-in date/time cannot be in the past.");
	}
}

void Booking::setCheckOut(const DateTime& check_out_) {
	if (isValidCheckOut(check_out_)) {
		this->check_out = check_out_;
	}
	else {
		throw std::invalid_argument("Error: Check-out date must be after check-in date.");
	}
}
void Booking::setCost(double room_price) {
	int number_of_nights = getNumberOfNights();
	this->cost = number_of_nights * room_price;
}

int Booking::getNumberOfNights() const {
	return getCheckOut() - getCheckIn();
}

std::string Booking::toString() const {
	std::ostringstream oss;
	oss << std::to_string(booking_id) << ","
		<< std::to_string(getCost()) << ","
		<< status << ","
		<< check_in.getDateTimeString() << ","
		<< check_out.getDateTimeString() << ","
		<< std::to_string(getRoomNumber()) << ","
		<< std::to_string(getCustomerId());
	return oss.str();
}

void Booking::printBookingInfo() const {
	std::cout << "\t\t\t Booking Number: " << getId() << '\n';
	std::cout << "\t\t\t Room Number: " << getRoomNumber() << '\n';
	std::cout << "\t\t\t Customer Id: " << getCustomerId() << '\n';
	std::cout << "\t\t\t Check-In: " << getCheckIn().getDateTimeString() << '\n';
	std::cout << "\t\t\t Check-Out: " << getCheckOut().getDateTimeString() << '\n';
	std::cout << "\t\t\t Booking Cost: " << getCost() << "\n";
	std::cout << "\t\t\t Booking Status: " << getStatus() << '\n';
	std::cout << '\n';
}