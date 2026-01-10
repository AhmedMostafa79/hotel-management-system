#include<chrono>
#include<string>
#include<iomanip>
#include<sstream>
#include<ctime>
#include "DateTime.h"
DateTime::DateTime() : m_time(std::chrono::system_clock::now()) {}

DateTime::DateTime(const std::string& dateTimeString) {
	std::istringstream iss(dateTimeString);
	std::tm tmStruct = {};
	iss >> std::get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
	if (iss.fail()) {
		throw std::invalid_argument("Invalid date-time format. Expected: YYYY-MM-DD HH:MM:SS");
	}
	m_time = std::chrono::system_clock::from_time_t(std::mktime(&tmStruct));
}

DateTime DateTime::operator+(int days) const {
	DateTime result = *this;
	result.m_time += std::chrono::hours(24 * days);
	return result;
}

int DateTime::operator-(const DateTime& other) const {
	auto duration = m_time - other.getTimePoint();
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
	return hours / 24;
}

bool DateTime::operator<=(const DateTime& rhs) const {
	return m_time <= rhs.m_time;
}

bool DateTime::operator>=(const DateTime& rhs) const {
	return m_time >= rhs.m_time;
}

bool DateTime::operator>(const DateTime& rhs) const {
	return m_time > rhs.m_time;
}

bool DateTime::operator<(const DateTime& rhs) const {
	return m_time < rhs.m_time;
}

void DateTime::setDateTime(const std::chrono::system_clock::time_point& new_time) {
	m_time = new_time;
}

void DateTime::setDateTime(const std::string& date_time_string) {
	std::istringstream iss(date_time_string);
	std::tm tmStruct = {};
	iss >> std::get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
	if (iss.fail()) {
		throw std::invalid_argument("Invalid date-time format. Expected: YYYY-MM-DD HH:MM:SS");
	}
	m_time = std::chrono::system_clock::from_time_t(std::mktime(&tmStruct));
}

void DateTime::setDateAtNoon() {
	std::time_t current_time = std::chrono::system_clock::to_time_t(m_time);
	std::tm tmStruct = {};

#ifdef _WIN32
	errno_t err = localtime_s(&tmStruct, &current_time);
	if (err != 0) {
		throw std::runtime_error("Failed to convert time");
	}
#else
	if (localtime_r(&current_time, &tmStruct) == nullptr) {
		throw std::runtime_error("Failed to convert time");
	}
#endif
	// Set time to 12:00:00 (noon) while keeping the same date
	tmStruct.tm_hour = 12;  // 12 PM
	tmStruct.tm_min = 0;
	tmStruct.tm_sec = 0;

	// Convert back to time_point and update member variable
	m_time = std::chrono::system_clock::from_time_t(std::mktime(&tmStruct));
}

std::string DateTime::getDateTimeString() const {
	std::time_t timeT = std::chrono::system_clock::to_time_t(m_time);
	std::tm tmStruct;

#ifdef _WIN32
	localtime_s(&tmStruct, &timeT);
#else
	localtime_r(&timeT, &tmStruct);
#endif

	std::ostringstream oss;
	oss << std::put_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

std::string DateTime::getTimeString() const {
	std::time_t timeT = std::chrono::system_clock::to_time_t(m_time);
	std::tm tmStruct;

#ifdef _WIN32
	localtime_s(&tmStruct, &timeT);
#else
	localtime_r(&timeT, &tmStruct);
#endif

	std::ostringstream oss;
	oss << std::put_time(&tmStruct, "%H:%M:%S");
	return oss.str();
}

std::string DateTime::getDateString() const {
	std::time_t timeT = std::chrono::system_clock::to_time_t(m_time);
	std::tm tmStruct;

#ifdef _WIN32
	localtime_s(&tmStruct, &timeT);
#else
	localtime_r(&timeT, &tmStruct);
#endif

	std::ostringstream oss;
	oss << std::put_time(&tmStruct, "%Y-%m-%d");
	return oss.str();
}

std::chrono::system_clock::time_point DateTime::getTimePoint() const {
	return m_time;
}