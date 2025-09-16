#include<bits/stdc++.h>
#include<regex>
#include<optional>
#include <chrono>
using namespace std;

// Helper Functions
// ================
/**
 * @brief Prompts the user and validates integer input.
 * @param prompt The message to display to the user.
 * @return int The validated integer input from the user.
 * @details Continuously prompts the user until valid integer input is received.
 *          Handles all error cases including non-numeric input and buffer cleanup.
 * @note Uses robust input validation with full buffer clearing to prevent
 *       any residual characters from affecting subsequent input operations.
 */
int getValidatedInt(const string& prompt) {
	int value;
	while (true) {
		cout << prompt;
		cin >> value;

		if (cin.fail()) {
			cout << "\t\tInvalid input. Please enter a number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
	}
}

/**
 * @brief Prompts the user and validates floating-point input.
 * @param prompt The message to display to the user.
 * @return double The validated double input from the user.
 * @details Continuously prompts the user until valid numeric input is received.
 *          Handles all error cases including non-numeric input and buffer cleanup.
 * @note Uses the same robust validation pattern as getValidatedInt() for consistency.
 */
double getValidatedDouble(const string& prompt) {
	double value;
	while (true) {
		cout << prompt;
		cin >> value;

		if (cin.fail()) {
			cout << "\t\tInvalid input. Please enter a number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
	}
}

/**
 * @brief Validates that an integer falls within a specified range.
 * @param low The lower bound of the valid range (inclusive).
 * @param high The upper bound of the valid range (inclusive).
 * @return int The validated integer within the specified range.
 * @details Uses getValidatedInt() for base validation, then checks range constraints.
 *          Provides specific error feedback for out-of-range values.
 */
int readInt(const int& low, const int& high) {
	while (true) {
		int num = getValidatedInt("\n\t\tEnter number in range " + to_string(low) + " - " + to_string(high) + " : ");
		cout << '\n';
		if (low <= num && num <= high) {
			return num;
		}
		cout << "\n\t\tInvalid number! Please try again.\n";
	}
}

/**
 * @brief Displays a menu and returns the user's validated selection.
 * @param menu_name The title to display for the menu.
 * @param choices Vector of strings representing the menu options.
 * @return int The user's selection (1-based index corresponding to the choices vector).
 * @details Presents a formatted menu with numbered options and uses readInt()
 *          to ensure the selection is valid for the given choices.
 * @note The return value ranges from 1 to choices.size() (inclusive).
 */
int showOuterReadMenu(const string& menu_name, const vector<string>& choices) {
	cout << "\n\n\t***** " << menu_name << " *****\n\n\n";
	for (int choice = 0; choice < choices.size(); choice++) {
		cout << "\t\tChoice " << choice + 1 << ". " << choices[choice] << '\n';
	}
	int choice = readInt(1, choices.size());
	return choice;
}
int showInnerReadMenu(const string& menu_name, const vector<string>& choices) {
	cout << "\n\n\t\t=== " << menu_name << " ===\n\n\n";
	for (int choice = 0; choice < choices.size(); choice++) {
		cout << "\t\t\tChoice " << choice + 1 << ". " << choices[choice] << '\n';
	}
	int choice = readInt(1, choices.size());
	return choice;
}
string toLowerCase(string s) {
	for (auto& i : s)
			tolower(i);
	return s;
}
/**
  * @class DateTime
  * @brief Represents a specific point in time with comprehensive formatting capabilities.
  * using the chrono library for internal storage and supporting string conversion
  * in standard ISO-like formats. It features cross-platform thread-safe implementation 
*/
class DateTime {
private:
	chrono::system_clock::time_point m_time;

public:
	/**
	  * @brief Default constructor.
	  * @details Initializes the DateTime object to current system time.
	*/
	DateTime() : m_time(chrono::system_clock::now()) {}

	/**
	  * @brief Constructor for formatted string. 
	  * @param dateTimeString String in "YYYY-MM-DD HH:MM:SS" format.
	  * @throw invalid_argument If the input string format is incorrect.
      * @details Parses a standardized date-time string to initialize the object.
	*/
	DateTime(const string& dateTimeString) {
		istringstream iss(dateTimeString);
		tm tmStruct = {};
		iss >> get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
		if (iss.fail()) {
			throw invalid_argument("Invalid date-time format. Expected: YYYY-MM-DD HH:MM:SS");
		}
		m_time = chrono::system_clock::from_time_t(mktime(&tmStruct));
	}
	/**
	* @brief Add days to the DateTime.
	* @param days Number of days to add.
	* @return New DateTime object with the added days.
	*/
	DateTime operator+(int days) const {
		DateTime result = *this;
		result.m_time += chrono::hours(24 * days);
		return result;
	}
	bool operator<=(const DateTime& rhs) const {
		return m_time <= rhs.m_time;
	}
	bool operator>=(const DateTime& rhs) const {
		return m_time >= rhs.m_time;
	}
	bool operator>(const DateTime& rhs) const {
		return m_time > rhs.m_time;
	}
	bool operator<(const DateTime& rhs) const {
		return m_time < rhs.m_time;
	}
	/**
	  * @brief Sets the time from a chrono::system_clock::time_point.
	  * @param newTime The new time point to set.
	  * @note This is a low-level interface for direct time_point manipulation.
	*/
	void setDateTime(const chrono::system_clock::time_point& new_time) {
		m_time = new_time;
	}

	/**
	  * @brief Sets the time by parsing a formatted string.
	  * @param dateTimeString String in "YYYY-MM-DD HH:MM:SS" format.
	  * @throw invalid_argument If the input string format is incorrect.
	*/
	void setDateTime(const string& date_time_string) {
		istringstream iss(date_time_string);
		tm tmStruct = {};
		iss >> get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
		if (iss.fail()) {
			throw invalid_argument("Invalid date-time format. Expected: YYYY-MM-DD HH:MM:SS");
		}
		m_time = chrono::system_clock::from_time_t(mktime(&tmStruct));
	}
	/**
	* @brief Sets the DateTime from a date string with time fixed to 12:00:00 PM.
	* @param dateString String in "YYYY-MM-DD" format.
	* @throw invalid_argument If the date format is incorrect.
	* @details Parses a date string and sets the time to noon (12:00:00).
	*/
	void setDateAtNoon(const string& date_string) {
		istringstream iss(date_string);
		tm tmStruct = {};

		iss >> get_time(&tmStruct, "%Y-%m-%d");
		if (iss.fail()) {
			throw invalid_argument("Invalid date format. Expected: YYYY-MM-DD");
		}

		 //Set time to 12:00:00 PM (noon).
		tmStruct.tm_hour = 11;
		tmStruct.tm_min = 0;
		tmStruct.tm_sec = 0;

		m_time = chrono::system_clock::from_time_t(mktime(&tmStruct));
	}

	int getDayDifference(const DateTime& other) const {
		// Get the time difference in hours
		auto duration = other.getTimePoint() - m_time;
		auto hours = chrono::duration_cast<chrono::hours>(duration).count();

		// Convert hours to days
		return hours / 24;
	}
	/**
	  * @brief Converts the DateTime to a standardized string representation.
	  * @return string Formatted as  "YYYY-MM-DD HH:MM:SS".
	  * @details Suitable for storage, logging, or display. Uses thread-safe conversion.
	*/
	string getDateTimeString() const {
		time_t timeT = chrono::system_clock::to_time_t(m_time);
		tm tmStruct;
#ifdef _WIN32
		localtime_s(&tmStruct, &timeT); // Windows-specific thread-safe function
#else
		localtime_r(&timeT, &tmStruct); // POSIX-specific thread-safe function
#endif
		ostringstream oss;
		oss << put_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	/**
	  * @brief Extracts the time portion of the DateTime.
	  * @return string Formatted as "HH:MM:SS".
	*/	
	string getTimeString() const {
		time_t timeT = chrono::system_clock::to_time_t(m_time);
		tm tmStruct;
#ifdef _WIN32
		localtime_s(&tmStruct, &timeT);
#else
		localtime_r(&timeT, &tmStruct);
#endif
		ostringstream oss;
		oss << put_time(&tmStruct, "%H:%M:%S");
		return oss.str();
	}
	/**
	  * @brief Extracts the date portion of the DateTime.
	  * @return string Formatted as "YYYY-MM-DD".
	*/
	string getDateString() const {
		time_t timeT = chrono::system_clock::to_time_t(m_time);
		tm tmStruct;
#ifdef _WIN32
		localtime_s(&tmStruct, &timeT);
#else
		localtime_r(&timeT, &tmStruct);
#endif
		ostringstream oss;
		oss << put_time(&tmStruct, "%Y-%m-%d");
		return oss.str();
	}

	

	/**
	  * @brief Gets the internal time_point representation.
	  * @return chrono::system_clock::time_point The underlying time point.
	  * @note Useful for calculations with the chrono library.
	*/
	chrono::system_clock::time_point getTimePoint() const {
		return m_time;
	}
};

/**
  * @class Room
  * @brief Represents a hotel room with its properties and state.
  *
  * This class encapsulates all the attributes and behaviors of a hotel room,
  * including its unique identifier, pricing, type, and current status.
  * It provides functionality to manage room details, calculate costs,
  * and serialize room information for storage and display.
  */

class Room {
	int room_number;        ///< Unique ID for the room.
	double price_per_night; ///< Cost for one night's stay in the room.
	string type;            ///< Category of the room(e.g. Standard,Deluxe).
	string status;          ///< Current state (e.g. Available, Occupied, Maintenance).
public:
	/**
	 * @brief Default Constructor.
	 * @details provides empty room object.
	 */
	Room();

	/**
	 * @brief Parameterized constructor. Creates a room with specified properties.
	 * @param room_num The unique number identifying the room.
	 * @param price The cost per night for the room.
	 * @param type The category/type of the room.
	 * @param status The initial status of the room.
	 */
	Room(int room_number, double price, const string& type, const string& status);
	// GETTERS AND SETTERS (kept inside - they are trivial)

	/**
	 * @brief Sets category/type of the room.
	 * @param type the new room type (Single, Double, Deluxe).
	 */
	void setType(const string& type) { this->type = type; }

	/**
	 * @brief Sets price per night for the room.
	 * @param price_ The new price per night.
	 */
	void setPrice(double price_) { this->price_per_night = price_; }

	/**
	 * @brief Sets the new status of the room.
	 * @param status The new Status(Available, Occupied).
	 */
	void setStatus(const string& status) { this->status = status; }

	/**
	 * @brief Gets type of the room
	 * @return Const string& a constant reference to the type string.
	 */
	const string& getType() const { return this->type; }

	/**
	 * @brief Gets price per night of the room.
	 * @return double the price.
	 */
	double getPrice() const { return this->price_per_night; }

	/**
	 * @brief Gets status of the room
	 * @return Const string& a constant reference to the status string.
	 */
	const string& getStatus() const { return this->status; }

	/**
	 * @brief Gets the room's unique identifier number.
	 * @return int the room number.
	 */
	int getNumber() const { return this->room_number; }

	// Utility Function Declarations
	/**
	 * @brief Serializes the Room object into string representation.
	 * @details the format is : "room_number,type,status,price_per_night".
	 * @return string a comma-separated string containing the room's data.
	 */
	string toString() const;

	/**
	 * @brief prints the room details to the standard output.
	 * @details the output is indented and formatted for console display in a formatted way.
	 */
	void printRoomDetails() const;
};

/**
  * @class RoomsManager
  * @brief Manages a collection of Room objects, handling their lifecycle and operations.
  *
  * This class is responsible for the management of all hotel rooms.
  * It provides functionality to add, search, update, and delete room records,
  * ensuring proper memory management through ownership of the Room pointers.
  * The manager handles room availability, pricing, and status management.
  */
class RoomsManager {
	vector<Room*> rooms;    ///< Container storing pointers to all managed Room objects
	int last_id;            ///< Tracks the last assigned room number to help generate new unique IDs.

	/**
	 * @brief Generates and returns a new unique room number.
	 * @details Increments the internal counter and returns the new value.
	 * @return int The newly generated room number.
	 */
	int getNewId() { return ++last_id; }

	/**
	 * @brief Finds a room pointer by room number.
	 * @param room_number The room number to search for.
	 * @return Room* Pointer to the room, or nullptr if not found.
	 */
	Room* findRoom(int room_number) const;

public:
	/**
	 * @brief Default Constructor. Initializes the room number counter.
	 */
	RoomsManager();

	/**
	 * @brief Destructor, Ensures proper cleanup of all managed room objects.
	 * @details Iterates through the rooms vector and deletes each dynamically allocated Room.
	 */
	~RoomsManager();

	// PUBLIC INTERFACE
	/**
	 * @brief Adds a room to manager's collection.
	 * @details The manager takes ownership of Room pointers and is responsible for its deletion.
	 * @param type The room type.
	 * @param status The room status.
	 * @param price The room price.
	 * @return optional<Room> The created room if successful.
	 */
	optional<Room> addNewRoom(const string& type, const string& status, double price);


	/**
	 * @brief Gets all rooms as value copies.
	 * @return vector<Room> Vector of all rooms.
	 */
	vector<Room> getAllRooms() const;

	/**
	 * @brief Gets the last added room number.
	 * @return int The room number, or -1 if no rooms.
	 */
	int getLastAdded() const;

	/**
	 * @brief Gets the number of managed rooms.
	 * @return int The count of rooms.
	 */
	int getNumberOfRooms() const;

	/**
	 * @brief Searches for a room by number.
	 * @param room_number The room number to search for.
	 * @return optional<Room> The room if found.
	 */
	optional<Room> searchForRoom(int room_number) const;

	/**
	 * @brief Checks if a room exists.
	 * @param room_number The room number to check.
	 * @return bool True if room exists.
	 */
	bool doesRoomExist(int room_number) const;

	/**
	 * @brief Updates room price.
	 * @param room_num The room number.
	 * @param price The new price.
	 * @return bool True if update successful.
	 */
	bool updateRoomPrice(int room_num, double price);

	/**
	 * @brief Updates room type.
	 * @param room_num The room number.
	 * @param type The new type.
	 * @return bool True if update successful.
	 */
	bool updateRoomType(int room_num, const string& type);

	/**
	 * @brief Updates room status.
	 * @param room_num The room number.
	 * @param status The new status.
	 * @return bool True if update successful.
	 */
	bool updateRoomStatus(int room_num, const string& status);

	/**
	 * @brief Gets rooms by status.
	 * @param status The status to filter by (default: "Available").
	 */
	void getRoomByStatus(const string& status = "Available") const;

	/**
	 * @brief Deletes a room.
	 * @param room_number The room number to delete.
	 * @return bool True if deletion successful.
	 */
	bool deleteRoom(int room_number);

	// Prevents any assignment for manager
	RoomsManager(const RoomsManager&) = delete;
	RoomsManager& operator=(const RoomsManager&) = delete;
};

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
	string name;            ///< Customer Name.
	string phone_number;    ///< Customer Phone Number (contact).
	string email;           ///< Customer Email (contact).
	/**
	 * @brief Validates an email address format.
	 * @details Checks if the email matches the basic pattern: local-part@domain.tld
	 * @param email_ The email address string to validate.
	 * @return bool True if the email format is valid, false otherwise.
	 */
	bool validateEmail(const string& email_)const; 
	/**
	 * @brief Validates a phone number format.
	 * @details Checks if the phone number contains only digits and has exactly 11 characters.
	 *          This assumes a standard 11-digit phone number format (e.g., 12345678901).
	 * @param phone The phone number string to validate.
	 * @return bool True if the phone number format is valid, false otherwise.
	 */
	bool validatePhoneNumber(const string& phone)const;
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
	Customer(int id, const string& name, int age, const string& phone, const string& email);

	// GETTERS AND SETTERS (kept inside - they are trivial)

	/**
	 * @brief Sets the customer's email address with validation.
	 * @param email_ The new email address to set.
	 * @throws std::invalid_argument if the email format is invalid.
	 * @note Uses validateEmail() for Validation before assignment.
	 */
	void setEmail(const string& email_); 

	/**
	 * @brief Sets the customer's phone number with validation.
	 * @param phone_ The new phone number to set.
	 * @throws std::invalid_argument if the phone number format is invalid.
	 * @note Uses validatePhoneNumber() for Validation before assignment.
	 */
	void setPhoneNumber(const string& phone);

	/**
	 * @brief Gets customer's unique identifier(ID).
	 * @return int The customer ID.
	 */
	int getId() const { return id; }

	/**
	 * @brief Gets customer's name.
	 * @return const string& Constant reference to the name string.
	 */
	const string& getName() const { return name; }

	/**
	 * @brief Gets customer's age.
	 * @return int The customer age.
	 */
	int getAge() const { return age; }

	/**
	 * @brief Gets customer's email.
	 * @return const string& Constant reference to the email string.
	 */
	const string& getEmail() const { return email; }

	/**
	 * @brief Gets customer's phone number.
	 * @return const string& Constant reference to the phone number string.
	 */
	const string& getPhoneNumber() const { return phone_number; }

	// COMPLEX FUNCTIONS (declared here, defined outside)
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
	string toString() const;

	/**
	 * @brief Prints the customer's information to standard output in a formatted way.
	 * @details the output is indented and formatted for console display.
	 */
	void printCustomerData() const;
};

/**
  * @class CustomersManager
  * @brief Manages a collection of Customer objects, handling their lifecycle and operations.
  *
  * This class is responsible for the management of all hotel customers.
  * It provides functionality to add, search, update, and delete customer records,
  * ensuring proper memory management through ownership of the Customer pointers.
  * The manager handles customer information, contact details, and customer data persistence.
  */
class CustomersManager {
	int last_id;                    ///< Last used customer identifier for generating new IDs.
	vector<Customer*> customers;    ///< Container storing pointers to all managed Customer objects.

	/**
	 * @brief Generates and returns a new unique customer ID.
	 * @return int The newly generated customer ID.
	 */
	int getNewId() { return ++last_id; }

	/**
	 * @brief Finds a customer pointer by customer ID.
	 * @param customer_id The customer ID to search for.
	 * @return Customer* Pointer to the customer, or nullptr if not found.
	 */
	Customer* findCustomer(int customer_id) const;

public:
	/**
	 * @brief Default constructor.
	 */
	CustomersManager();

	/**
	 * @brief Destructor.
	 * @details Cleans up all dynamically allocated Customer objects.
	 */
	~CustomersManager();

	/**
	 * @brief Gets the number of managed customers.
	 * @return int Count of customers.
	 */
	int getNumberOfCustomers() const;

	/**
	 * @brief Gets all customers as value copies.
	 * @return vector<Customer> Vector of all customers.
	 */
	vector<Customer> getAllCustomers() const;

	/**
	 * @brief Gets the last added customer ID.
	 * @return int The customer ID, or -1 if no customers.
	 */
	int getLastAdded() const;

	/**
	 * @brief Searches for a customer by ID.
	 * @param customer_id The customer ID to search for.
	 * @return optional<Customer> The customer if found.
	 */
	optional<Customer> searchForCustomer(int customer_id) const;

	/**
	 * @brief Checks if a customer exists.
	 * @param customer_id The customer ID to check.
	 * @return bool True if customer exists.
	 */
	bool doesCustomerExist(int customer_id) const;

	/**
	 * @brief Adds a new customer to the manager.
	 * @param name Customer name.
	 * @param age Customer age.
	 * @param phone Customer phone number.
	 * @param email Customer email address.
	 * @return optional<Customer> The created customer if successful.
	 */
	optional<Customer> addNewCustomer(const string& name, int age, const string& phone, const string& email);

	/**
	 * @brief Updates the email address for a customer.
	 * @param customer_id Customer identifier.
	 * @param email New email address.
	 * @return bool True if update successful.
	 */
	bool updateCustomerEmail(int customer_id, const string& email);

	/**
	 * @brief Updates the phone number for a customer.
	 * @param customer_id Customer identifier.
	 * @param phone New phone number.
	 * @return bool True if update successful.
	 */
	bool updateCustomerPhone(int customer_id, const string& phone);

	/**
	 * @brief Deletes a customer.
	 * @param customer_id Customer identifier to delete.
	 * @return bool True if deletion successful.
	 */
	bool deleteCustomer(int customer_id);

	// Prevents any assignment for manager
	CustomersManager(const CustomersManager&) = delete;
	CustomersManager& operator=(const CustomersManager&) = delete;
};

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
	string status;          ///< Booking status: (Pending, Done, Cancelled).
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
	bool isValidStatus(string status)const ;
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
		const DateTime& check_in, const DateTime& check_out, const string& status);

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
	void setStatus(const string& status_);

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
	const string& getStatus() const { return this->status; }

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
	string toString() const;

	/**
	 * @brief Prints booking details.
	 */
	void printBookingData() const;
};
/**
  * @class BookingsManager
  * @brief Manages a collection of Booking objects, handling their lifecycle and operations.
  *
  * This class is responsible for the management of all hotel bookings.
  * It provides functionality to create, search, update, and delete booking records,
  * ensuring proper memory management through ownership of the Booking pointers.
  * The manager handles booking conflicts, date validation, cost calculations,
  * and maintains the relationship between rooms and customers through bookings.
  */
class BookingsManager {
	int last_id;                    ///< Last used booking identifier for generating new IDs.
	vector<Booking*> bookings;      ///< Container storing pointers to all managed Booking objects.

	/**
	 * @brief Generates and returns a new unique booking ID.
	 * @return int The newly generated booking ID.
	 */
	int getNewId() { return ++last_id; }

	/**
	 * @brief Finds a booking pointer by booking ID.
	 * @param booking_id The booking ID to search for.
	 * @return Booking* Pointer to the booking, or nullptr if not found.
	 */
	Booking* findBooking(int booking_id) const;

public:
	/**
	 * @brief Default constructor.
	 */
	BookingsManager();

	/**
	 * @brief Destructor.
	 * @details Cleans up all dynamically allocated Booking objects.
	 */
	~BookingsManager();

	/**
	 * @brief Gets the number of managed bookings.
	 * @return int Count of bookings.
	 */
	int getNumberOfBookings() const;

	/**
	 * @brief Gets all bookings as value copies.
	 * @return vector<Booking> Vector of all bookings.
	 */
	vector<Booking> getAllBookings() const;

	/**
	 * @brief Gets bookings for a specific room.
	 * @param room_number The room number to filter by.
	 * @return vector<Booking> Vector of bookings for the room.
	 */
	vector<Booking> getBookingsByRoom(int room_number) const;

	/**
	 * @brief Gets the last added booking ID.
	 * @return int The booking ID, or -1 if no bookings.
	 */
	int getLastAdded() const;

	/**
	 * @brief Searches for a booking by ID.
	 * @param booking_number The booking ID to search for.
	 * @return optional<Booking> The booking if found.
	 */
	optional<Booking> searchForBooking(int booking_number) const;

	/**
	 * @brief Checks if a booking exists.
	 * @param booking_id The booking ID to check.
	 * @return bool True if booking exists.
	 */
	bool doesBookingExist(int booking_id) const;

	/**
	 * @brief Adds a new booking to the manager.
	 * @param customer_id Customer identifier.
	 * @param room_number Room number.
	 * @param room_price Price per night.
	 * @param chin Check-in date.
	 * @param chout Check-out date.
	 * @return optional<Booking> The created booking if successful.
	 */
	optional<Booking> addNewBooking(int customer_id, int room_number, double room_price,
		const DateTime& chin, const DateTime& chout);

	/**
	 * @brief Updates the room number for a booking.
	 * @param booking_id Booking identifier.
	 * @param room_number New room number.
	 * @return bool True if update successful.
	 */
	bool updateRoom(int booking_id, int room_number);

	/**
	 * @brief Updates the status of a booking.
	 * @param booking_id Booking identifier.
	 * @param status New status.
	 * @return bool True if update successful.
	 */
	bool updateBookingStatus(int booking_id, const string& status);

	/**
	 * @brief Updates the dates of a booking.
	 * @param booking_id Booking identifier.
	 * @param chin New check-in date.
	 * @param chout New check-out date.
	 * @return bool True if update successful.
	 */
	bool updateBookingDates(int booking_id, const DateTime& chin, const DateTime& chout);

	/**
	 * @brief Deletes a booking.
	 * @param booking_id Booking identifier to delete.
	 * @return bool True if deletion successful.
	 */
	bool deleteBooking(int booking_id);

	// Prevents any assignment for manager
	BookingsManager(const BookingsManager&) = delete;
	BookingsManager& operator=(const BookingsManager&) = delete;
};

  /**
	* @class HotelManager
	* @brief Central management class that coordinates all hotel operations and subsystems.
	*
	* This class serves as the main facade for the hotel management system,
	* providing a unified interface to manage rooms, customers, and bookings.
	* It orchestrates the interactions between RoomsManager, CustomersManager,
	* and BookingsManager, ensuring data consistency and business rule enforcement
	* across all hotel operations including availability checks, booking conflicts,
	* and customer-room relationships.
	*/
class HotelManager {
	RoomsManager rooms_manager;         ///< Manages all room-related operations and data.
	CustomersManager customers_manager; ///< Manages all customer-related operations and data.
	BookingsManager bookings_manager;   ///< Manages all booking-related operations and data.

	/**
	 * @brief Gets reference to the RoomsManager subsystem.
	 * @return RoomsManager& Reference to the rooms manager.
	 */
	RoomsManager& getRoomsManager();

	/**
	 * @brief Gets reference to the CustomersManager subsystem.
	 * @return CustomersManager& Reference to the customers manager.
	 */
	CustomersManager& getCustomersManager();

	/**
	 * @brief Gets reference to the BookingsManager subsystem.
	 * @return BookingsManager& Reference to the bookings manager.
	 */
	BookingsManager& getBookingsManager();

public:
	/**
	 * @brief Default constructor.
	 */
	HotelManager();

	/**
	 * @brief Checks if a room exists.
	 * @param room_number The room number to check.
	 * @return bool True if room exists.
	 */
	bool doesRoomExist(int room_number) const;

	/**
	 * @brief Checks if a customer exists.
	 * @param customer_id The customer ID to check.
	 * @return bool True if customer exists.
	 */
	bool doesCustomerExist(int customer_id) const;

	/**
	 * @brief Checks if a booking exists.
	 * @param booking_id The booking ID to check.
	 * @return bool True if booking exists.
	 */
	bool doesBookingExist(int booking_id) const;

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
	vector<Room> getAvailableRooms(const DateTime& check_in, const DateTime& check_out) const;

	/**
	 * @brief Gets a room by its number.
	 * @param room_num The room number.
	 * @return optional<Room> The room if found.
	 */
	optional<Room> getRoomByNumber(int room_num) const;

	/**
	 * @brief Gets a customer by their ID.
	 * @param customer_id The customer ID.
	 * @return optional<Customer> The customer if found.
	 */
	optional<Customer> getCustomerById(int customer_id) const;

	/**
	 * @brief Gets a booking by its ID.
	 * @param booking_id The booking ID.
	 * @return optional<Booking> The booking if found.
	 */
	optional<Booking> getBookingById(int booking_id) const;

	/**
	 * @brief Gets all rooms.
	 * @return vector<Room> List of all rooms.
	 */
	const vector<Room> getAllRooms() const;

	/**
	 * @brief Gets all customers.
	 * @return vector<Customer> List of all customers.
	 */
	vector<Customer> getAllCustomers() const;

	/**
	 * @brief Gets all bookings.
	 * @return vector<Booking> List of all bookings.
	 */
	vector<Booking> getAllBookings() const;

	/**
	 * @brief Gets the last added room number.
	 * @return int Last room number, or -1 if none.
	 */
	int getLastAddedRoom() const;

	/**
	 * @brief Gets the last added customer ID.
	 * @return int Last customer ID, or -1 if none.
	 */
	int getLastAddedCustomer() const;

	/**
	 * @brief Gets the last added booking ID.
	 * @return int Last booking ID, or -1 if none.
	 */
	int getLastAddedBooking() const;

	/**
	 * @brief Updates room price.
	 * @param room_number Room number.
	 * @param price New price.
	 * @return bool True if update successful.
	 */
	bool updateRoomPrice(int room_number, double price);

	/**
	 * @brief Updates room type.
	 * @param room_number Room number.
	 * @param type New room type.
	 * @return bool True if update successful.
	 */
	bool updateRoomType(int room_number, const string& type);

	/**
	 * @brief Updates room status.
	 * @param room_number Room number.
	 * @param status New room status.
	 * @return bool True if update successful.
	 */
	bool updateRoomStatus(int room_number, const string& status);

	/**
	 * @brief Updates customer phone number.
	 * @param customer_id Customer ID.
	 * @param phone New phone number.
	 * @return bool True if update successful.
	 */
	bool updateCustomerPhone(int customer_id, const string& phone);

	/**
	 * @brief Updates customer email.
	 * @param customer_id Customer ID.
	 * @param email New email address.
	 * @return bool True if update successful.
	 */
	bool updateCustomerEmail(int customer_id, const string& email);

	/**
	 * @brief Updates booking room number.
	 * @param booking_id Booking ID.
	 * @param new_room_number New room number.
	 * @return bool True if update successful.
	 */
	bool updateBookingRoom(int booking_id, int new_room_number);

	/**
	 * @brief Updates booking status.
	 * @param booking_id Booking ID.
	 * @param status New booking status.
	 * @return bool True if update successful.
	 */
	bool updateBookingStatus(int booking_id, const string& status);

	/**
	 * @brief Updates booking dates.
	 * @param booking_id Booking ID.
	 * @param check_in New check-in date.
	 * @param check_out New check-out date.
	 * @return bool True if update successful.
	 */
	bool updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out);

	/**
	 * @brief Adds a new room.
	 * @param type Room type.
	 * @param status Room status.
	 * @param price Room price.
	 * @return optional<Room> The created room if successful.
	 */
	optional<Room> addNewRoom(const string& type, const string& status, double price);

	/**
	 * @brief Adds a new customer.
	 * @param name Customer name.
	 * @param age Customer age.
	 * @param phone Customer phone number.
	 * @param email Customer email address.
	 * @return optional<Customer> The created customer if successful.
	 */
	optional<Customer> addNewCustomer(const string& name, int age, const string& phone, const string& email);

	/**
	 * @brief Adds a new booking.
	 * @param date Booking date string.
	 * @param days Number of days to stay.
	 * @param customer_id Customer ID.
	 * @param room_number Room number.
	 * @return optional<Booking> The created booking if successful.
	 */
	optional<Booking> addNewBooking(const string& date, int days, int customer_id, int room_number);

	/**
	 * @brief Deletes a room.
	 * @param room_number Room number to delete.
	 * @return bool True if deletion successful.
	 */
	bool deleteRoom(int room_number);

	/**
	 * @brief Deletes a customer.
	 * @param customer_id Customer ID to delete.
	 * @return bool True if deletion successful.
	 */
	bool deleteCustomer(int customer_id);

	/**
	 * @brief Deletes a booking.
	 * @param booking_id Booking ID to delete.
	 * @return bool True if deletion successful.
	 */
	bool deleteBooking(int booking_id);

	// Prevents any assignment for manager
	HotelManager(const HotelManager&) = delete;
	HotelManager& operator=(const HotelManager&) = delete;
};


/**
  * @class HotelUI
  * @brief User interface class for interacting with the hotel management system.
  *
  * This class provides a comprehensive user interface for all hotel operations,
  * including room management, customer management, booking operations, and
  * display functionalities. It serves as the presentation layer that interacts
  * with users through the console while delegating business logic to HotelManager.
  */
class HotelUI {
	HotelManager& hotel_manager;    ///< Reference to the hotel manager for business operations.

	/**
	 * @brief Gets reference to the hotel manager.
	 * @return HotelManager& Reference to the hotel manager.
	 */
	HotelManager& getHotelManager() const;

public:
	/**
	 * @brief Constructor.
	 * @param manager Reference to the HotelManager instance.
	 */
	HotelUI(HotelManager& manager);

	/**
	 * @brief Displays available rooms for given dates.
	 * @param chin Check-in date.
	 * @param chout Check-out date.
	 */
	void printAvailableRoomsUI(const DateTime& chin, const DateTime& chout) const;

	/**
	 * @brief Displays all rooms in the system.
	 */
	void printAllRoomsUI() const;

	/**
	 * @brief Displays all customers in the system.
	 */
	void printAllCustomersUI() const;

	/**
	 * @brief Displays all bookings in the system.
	 */
	void printAllBookingsUI() const;

	/**
	 * @brief Displays room details by room number.
	 */
	void printRoomByNumberUI() const;

	/**
	 * @brief Displays customer details by customer ID.
	 */
	void printCustomerByIdUI() const;

	/**
	 * @brief Displays booking details by booking ID.
	 */
	void printBookingByIDUI() const;

	/**
	 * @brief Adds a new room through user interface.
	 */
	void addNewRoomUI();

	/**
	 * @brief Adds a new customer through user interface.
	 */
	void addNewCustomerUI();

	/**
	 * @brief Adds a new booking through user interface.
	 */
	void addNewBookingUI();

	/**
	 * @brief Deletes a room through user interface.
	 */
	void deleteRoomUI();

	/**
	 * @brief Deletes a customer through user interface.
	 */
	void deleteCustomerUI();

	/**
	 * @brief Deletes a booking through user interface.
	 */
	void deleteBookingUI();

	/**
	 * @brief Modifies room details through user interface.
	 */
	void modifyRoomUI();

	/**
	 * @brief Modifies customer details through user interface.
	 */
	void modifyCustomerUI();

	/**
	 * @brief Modifies booking details through user interface.
	 */
	void modifyBookingUI();
};


/**
  * @class HotelSystem
  * @brief Main system class that coordinates the entire hotel management application.
  *
  * This class serves as the entry point and central coordinator for the hotel management system.
  * It manages the interaction between the business logic (HotelManager) and user interface (HotelUI),
  * provides role-based access control, and orchestrates the complete menu navigation system
  * for administrators and receptionists.
  */
class HotelSystem {
	HotelManager hotel_manager;    ///< Manages all hotel business logic and data.
	HotelUI hotel_ui;              ///< Handles user interface and presentation layer.

	/**
	 * @brief Gets reference to the hotel UI.
	 * @return HotelUI& Reference to the hotel user interface.
	 */
	HotelUI& getHotelUI();

	/**
	 * @brief Gets reference to the hotel manager.
	 * @return HotelManager& Reference to the hotel manager.
	 */
	HotelManager& getHotelManager();

	/**
	 * @brief Displays admin room management menu.
	 */
	void showAdminRoomManagement();

	/**
	 * @brief Displays receptionist room operations menu.
	 */
	void showReceptionistRoomOperations();

	/**
	 * @brief Displays customer management menu.
	 */
	void showCustomerManagementMenu();

	/**
	 * @brief Displays booking management menu.
	 */
	void showBookingManagementMenu();

	/**
	 * @brief Displays admin main menu.
	 */
	void showAdminMenu();

	/**
	 * @brief Displays receptionist main menu.
	 */
	void showReceptionistMenu();

	/**
	 * @brief Validates password for role-based access.
	 * @param role The role to validate (admin or reception).
	 * @return bool True if password is correct.
	 */
	bool checkPassword(const string& role);

	/**
	 * @brief Displays the main application menu.
	 */
	void showMainMenu();

public:
	/**
	 * @brief Constructor.
	 */
	HotelSystem();

	/**
	 * @brief Runs the hotel management system.
	 */
	void run();
};


	//Room Class

	//Constructors  Definition
	Room::Room() : room_number(-1), price_per_night(0), type(""), status("") {}
	Room::Room(int room_number, double price, const string & type, const string & status)
		: room_number(room_number), price_per_night(price), type(type), status(status) {
	}
	//Public Functions Definition.
	string Room::toString() const {
		ostringstream room_info;
		room_info << to_string(room_number) << "," << type << "," << status << "," << to_string(price_per_night);
		return room_info.str();
	}

	void Room::printRoomDetails() const {
		cout << "\t\t\t number: " << getNumber() << "\n";
		cout << "\t\t\t type: " << getType() << '\n';
		cout << "\t\t\t price: " << getPrice() << '\n';
		cout << "\t\t\t status: " << getStatus() << "\n";
		cout << "\n";
	}

	//RoomsManager Class
	//Private Functions Definition
	Room* RoomsManager::findRoom(int room_number) const {
		for (const auto& room : rooms) {
			if (room->getNumber() == room_number)
				return room;
		}
		return nullptr;
	}

	// Constructor/Destructor Defintions
	RoomsManager::RoomsManager() : last_id(0) {}

	RoomsManager::~RoomsManager() {
		for (auto room : rooms) {
			delete room;
		}
		rooms.clear();
	}

	//Public Functions Definition
	optional<Room> RoomsManager::addNewRoom(const string& type, const string& status, double price) {
		Room* room = new Room(getNewId(), price, type, status);
		rooms.emplace_back(room);
		return *room;
	}
	vector<Room> RoomsManager::getAllRooms() const {
		vector<Room> temp;
		for (const auto& room : rooms)
			temp.push_back(*room);
		return temp;
	}
	int RoomsManager::getNumberOfRooms()const {
		return rooms.size();
	}
	int RoomsManager::getLastAdded() const {
		if (rooms.empty())
			return -1;
		return rooms.back()->getNumber();
	}

    optional<Room> RoomsManager::searchForRoom(int room_number) const {  
       for (const auto& room : rooms) {  
           if (room->getNumber() == room_number) {  
			   return  *room ; // Wrap the Room object in std::optional  
           }  
       }  
       return nullopt;  
    }

	bool RoomsManager::doesRoomExist(int room_number) const {
		optional<Room> temp_room = searchForRoom(room_number);
		return temp_room.has_value();
	}

	bool RoomsManager::updateRoomPrice(int room_num, double price) {
		if (doesRoomExist(room_num) == false)
			return false;
		Room* room = findRoom(room_num);
		room->setPrice(price);
		return true;
	}

	bool RoomsManager::updateRoomType(int room_num, const string& type) {
		if (doesRoomExist(room_num) == false)
			return false;
		Room* room = findRoom(room_num);
		room->setType(type);
		return true;
	}

	bool RoomsManager::updateRoomStatus(int room_num, const string& status) {
		if (doesRoomExist(room_num) == false)
			return false;
		Room* room = findRoom(room_num);
		room->setStatus(status);
		return true;
	}

	void RoomsManager::getRoomByStatus(const string& status) const {
		vector<Room> all_rooms = getAllRooms();
		cout << "\t" + status + " Rooms: \n";
		for (const auto& room : all_rooms) {
			if (room.getStatus() == status) {
				room.printRoomDetails();
				cout << "\n";
			}
		}
		cout << '\n';
	}

	bool RoomsManager::deleteRoom(int room_number) {
		if (doesRoomExist(room_number) == false)
			return false;

		auto it = rooms.begin();
		for (; it != rooms.end(); it++) {
			if ((*it)->getNumber() == room_number) {
				break;
			}
		}

		if (it != rooms.end()) {
			Room* room_to_delete = *it;
			rooms.erase(it);
			delete room_to_delete;
			return true;
		}
		return false;
	}

	//Customer Class 
	// 
	// CONSTRUCTOR DEFINITIONS
	Customer::Customer() : id(0), age(0), name(""), phone_number(""), email("") {}

	Customer::Customer(int id, const string& name, int age, const string& phone, const string& email)
		: id(id), age(age), name(name) {
		setEmail(email);
		setPhoneNumber(phone);
	}
	//Private Function Definitions 
	bool Customer::validateEmail(const string& email_)const {
		const regex pattern(R"(\w+@\w+\.\w+)");
		return regex_match(email_, pattern);
	}
	bool Customer::validatePhoneNumber(const string& phone)const {
		for (const auto& i : phone) {
			if (!isdigit(i))
				return false;
		}
		return phone.size()==11;
	}

	// Public FUNCTION DEFINITIONS
	void  Customer::setPhoneNumber(const string&phone_) {
		if (validatePhoneNumber(phone_)) {
			phone_number = phone_;
		}
		else {
			throw invalid_argument("Error!  Invalid phone number.");
		}
	}
	void Customer::setEmail(const string& email_){
		if (validateEmail(email_))
			this->email = email_;
		else {
			throw invalid_argument("Error!  Invalid email format.");
		}
	}
	bool Customer::operator==(const Customer& other) const {
		return getId() == other.getId();
	}

	string Customer::toString() const {
		ostringstream ss;
		ss << to_string(id) << "," << name << "," << to_string(age) << "," << phone_number << "," << email;
		return ss.str();
	}

	void Customer::printCustomerData() const {
		cout << "\t\t\tName: " << getName() << "\n";
		cout << "\t\t\tID: " << getId() << '\n';
		cout << "\t\t\tAge: " << getAge() << '\n';
		cout << "\t\t\tPhone Number: " << getPhoneNumber() << '\n';
		cout << "\t\t\tEmail: " << getEmail() << '\n';
		cout << "\n";
	}

	//CustomersManager Class 
		// Private Function Definition
		Customer* CustomersManager::findCustomer(int customer_id) const {
			for (const auto& customer : customers) {
				if (customer->getId() == customer_id)
					return customer;
			}
			return nullptr;
		}

		// Constructor/Destructor Definition
		CustomersManager::CustomersManager() : last_id(0) {}

		CustomersManager::~CustomersManager() {
			for (auto customer : customers)
				delete customer;
			customers.clear();
		}

		// Public Function Definition
		int CustomersManager::getNumberOfCustomers() const {
			return customers.size();
		}

		vector<Customer> CustomersManager::getAllCustomers() const {
			vector<Customer> temp;
			for (auto customer : customers)
				temp.push_back(*customer);
			return temp;
		}

		int CustomersManager::getLastAdded() const {
			if (customers.empty())
				return -1;
			return customers.back()->getId();
		}

		optional<Customer> CustomersManager::searchForCustomer(int customer_id) const {
			for (const auto& customer : customers) {
				if (customer->getId() == customer_id)
					return *customer;
			}
			return nullopt;
		}

		bool CustomersManager::doesCustomerExist(int customer_id) const {
			optional<Customer> customer = searchForCustomer(customer_id);
			return customer.has_value();
		}

		optional<Customer> CustomersManager::addNewCustomer(const string& name, int age, const string& phone, const string& email) {
			Customer* customer = new Customer(getNewId(), name, age, phone, email);
			customers.emplace_back(customer);
			return *customer;
		}

		bool CustomersManager::updateCustomerEmail(int customer_id, const string& email) {
			if (doesCustomerExist(customer_id) == false)
				return false;
			Customer* customer = findCustomer(customer_id);
			customer->setEmail(email);
			return true;
		}

		bool CustomersManager::updateCustomerPhone(int customer_id, const string& phone) {
			if (doesCustomerExist(customer_id) == false)
				return false;
			Customer* customer = findCustomer(customer_id);
			customer->setPhoneNumber(phone);
			return true;
		}

		bool CustomersManager::deleteCustomer(int customer_id) {
			if (doesCustomerExist(customer_id) == false)
				return false;

			auto it = customers.begin();
			for (; it != customers.end(); it++) {
				if ((*it)->getId() == customer_id)
					break;
			}

			if (it != customers.end()) {
				Customer* customer_to_delete = *it;
				customers.erase(it);
				delete customer_to_delete;
				return true;
			}
			return false;
		}

	//Booking Class

	// Constructor/Destructor Definition
	Booking::Booking() : booking_id(-1), cost(0), room_number(0), customer_id(0), status("") {}

	Booking::Booking(int booking_id, int room_id, int customer_id, double room_price,
		const DateTime& check_in, const DateTime& check_out, const string& status)
		: booking_id(booking_id), room_number(room_id), customer_id(customer_id)
		{
		setStatus(status);
		setCheckIn(check_in);
		setCheckOut(check_out);
		setCost(room_price);
	}
	//Private Function Definitions

	bool Booking::isValidStatus(string status)const {
		for (auto& i : status)
			i = tolower(i);
		return status == "pending" or status == "done" or status == "cancelled";
	}
	bool Booking::isValidCheckIn(const DateTime& check_in)const {
		return  check_in >= DateTime();
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

	void Booking::setStatus(const string& status_) {
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
		return getCheckIn().getDayDifference(getCheckOut());
	}

	string Booking::toString() const {
		ostringstream oss;
		oss << to_string(booking_id) << ","
			<< to_string(getCost()) << ","
			<< status << ","
			<< check_in.getDateTimeString() << ","
			<< check_out.getDateTimeString() << ","
			<< to_string(getRoomNumber()) << ","
			<< to_string(getCustomerId());
		return oss.str();
	}

	void Booking::printBookingData() const {
		cout << "\t\t\t Booking Number: " << getId() << '\n';
		cout << "\t\t\t Room Number: " << getRoomNumber() << '\n';
		cout << "\t\t\t Customer Id: " << getCustomerId() << '\n';
		cout << "\t\t\t Check-In: " << getCheckIn().getDateTimeString() << '\n';
		cout << "\t\t\t Check-Out: " << getCheckOut().getDateTimeString() << '\n';
		cout << "\t\t\t Booking Cost: " << getCost() << "\n";
		cout << "\t\t\t Booking Status: " << getStatus() << '\n';
		cout << '\n';
	}

	//BookingsManager Class
	
		// Private Function Definitions
		Booking* BookingsManager::findBooking(int booking_id) const {
			for (const auto& booking : bookings) {
				if (booking->getId() == booking_id)
					return booking;
			}
			return nullptr;
		}

		// Constructor/Destructor Definitions
		BookingsManager::BookingsManager() : last_id(0) {}

BookingsManager::~BookingsManager() {
	for (auto booking : bookings)
		delete booking;
	bookings.clear();
}

// Public Function Definitions
int BookingsManager::getNumberOfBookings() const {
	return bookings.size();
}

vector<Booking> BookingsManager::getAllBookings() const {
	vector<Booking> temp;
	for (auto booking : bookings)
		temp.push_back(*booking);
	return temp;
}

vector<Booking> BookingsManager::getBookingsByRoom(int room_number) const {
	vector<Booking> room_bookings;
	for (const auto& booking : bookings) {
		if (booking->getRoomNumber() == room_number)
			room_bookings.push_back(*booking);
	}
	return room_bookings;
}

int BookingsManager::getLastAdded() const {
	if (bookings.empty())
		return -1;
	return bookings.back()->getId();
}

optional<Booking> BookingsManager::searchForBooking(int booking_number) const {
	for (const auto& booking : bookings) {
		if (booking->getId() == booking_number)
			return *booking;
	}
	return nullopt;
}

bool BookingsManager::doesBookingExist(int booking_id) const {
	optional<Booking> booking = searchForBooking(booking_id);
	return booking.has_value();
}

optional<Booking> BookingsManager::addNewBooking(int customer_id, int room_number, double room_price,
	const DateTime& chin, const DateTime& chout) {
	Booking* booking = new Booking(getNewId(), room_number, customer_id, room_price, chin, chout, "Pending");
	bookings.push_back(booking);
	return *booking;
}

bool BookingsManager::updateRoom(int booking_id, int room_number) {
	if (doesBookingExist(booking_id) == false)
		return false;
	Booking* booking = findBooking(booking_id);
	booking->setRoomNumber(room_number);
	return true;
}

bool BookingsManager::updateBookingStatus(int booking_id, const string& status) {
	if (doesBookingExist(booking_id) == false)
		return false;
	Booking* booking = findBooking(booking_id);
	booking->setStatus(status);
	return true;
}

bool BookingsManager::updateBookingDates(int booking_id, const DateTime& chin, const DateTime& chout) {
	if (doesBookingExist(booking_id) == false)
		return false;
	Booking* booking = findBooking(booking_id);
	booking->setCheckIn(chin);
	booking->setCheckOut(chout);
	return true;
}

bool BookingsManager::deleteBooking(int booking_id) {
	if (doesBookingExist(booking_id) == false)
		return false;

	auto it = bookings.begin();
	for (; it != bookings.end(); it++) {
		if ((*it)->getId() == booking_id)
			break;
	}

	if (it != bookings.end()) {
		Booking* booking_to_delete = *it;
		bookings.erase(it);
		delete booking_to_delete;
		return true;
	}
	return false;
}

	//HotelManager
			// Private Function Definitions
			RoomsManager& HotelManager::getRoomsManager() {
				return rooms_manager;
			}

			CustomersManager& HotelManager::getCustomersManager() {
				return customers_manager;
			}

			BookingsManager& HotelManager::getBookingsManager() {
				return bookings_manager;
			}

			// Constructor Definition
			HotelManager::HotelManager() {}

			// Public Function Definitions
			bool HotelManager::doesRoomExist(int room_number) const {
				return rooms_manager.doesRoomExist(room_number);
			}

			bool HotelManager::doesCustomerExist(int customer_id) const {
				return customers_manager.doesCustomerExist(customer_id);
			}

			bool HotelManager::doesBookingExist(int booking_id) const {
				return bookings_manager.doesBookingExist(booking_id);
			}

			bool HotelManager::isRoomAvailableForDate(int room_number, const DateTime& check_in,
				const DateTime& check_out, int exclude_booking_id) const {
				auto room_bookings = bookings_manager.getBookingsByRoom(room_number);
				for (const auto& other_booking : room_bookings) {
					if (exclude_booking_id == other_booking.getId())
						continue;
					if (other_booking.isOverlapping(check_in, check_out)) {
						return false;
					}
				}
				return true;
			}

			vector<Room> HotelManager::getAvailableRooms(const DateTime& check_in, const DateTime& check_out) const {
				vector<bool> is_room_booked(rooms_manager.getNumberOfRooms() + 1, 0);
				vector<Room> available_rooms;
				vector<Booking> all_bookings = bookings_manager.getAllBookings();

				for (const auto& booking : all_bookings) {
					int room_num = booking.getRoomNumber();
					if (booking.isOverlapping(check_in, check_out)) {
						is_room_booked[room_num] = 1;
					}
				}

				for (const auto& room : rooms_manager.getAllRooms()) {
					int room_num = room.getNumber();
					if (is_room_booked[room_num] == 0)
						available_rooms.push_back(room);
				}

				return available_rooms;
			}

			optional<Room> HotelManager::getRoomByNumber(int room_num) const {
				return rooms_manager.searchForRoom(room_num);
			}

			optional<Customer> HotelManager::getCustomerById(int customer_id) const {
				return customers_manager.searchForCustomer(customer_id);
			}

			optional<Booking> HotelManager::getBookingById(int booking_id) const {
				return bookings_manager.searchForBooking(booking_id);
			}

			const vector<Room> HotelManager::getAllRooms() const {
				return rooms_manager.getAllRooms();
			}

			vector<Customer> HotelManager::getAllCustomers() const {
				return customers_manager.getAllCustomers();
			}

			vector<Booking> HotelManager::getAllBookings() const {
				return bookings_manager.getAllBookings();
			}

			int HotelManager::getLastAddedRoom() const {
				return rooms_manager.getLastAdded();
			}

			int HotelManager::getLastAddedCustomer() const {
				return customers_manager.getLastAdded();
			}

			int HotelManager::getLastAddedBooking() const {
				return bookings_manager.getLastAdded();
			}

			bool HotelManager::updateRoomPrice(int room_number, double price) {
				return rooms_manager.updateRoomPrice(room_number, price);
			}

			bool HotelManager::updateRoomType(int room_number, const string& type) {
				return rooms_manager.updateRoomType(room_number, type);
			}

			bool HotelManager::updateRoomStatus(int room_number, const string& status) {
				return rooms_manager.updateRoomStatus(room_number, status);
			}

			bool HotelManager::updateCustomerPhone(int customer_id, const string& phone) {
				return customers_manager.updateCustomerPhone(customer_id, phone);
			}

			bool HotelManager::updateCustomerEmail(int customer_id, const string& email) {
				return customers_manager.updateCustomerEmail(customer_id, email);
			}

			bool HotelManager::updateBookingRoom(int booking_id, int new_room_number) {
				return bookings_manager.updateRoom(booking_id, new_room_number);
			}

			bool HotelManager::updateBookingStatus(int booking_id, const string& status) {
				return bookings_manager.updateBookingStatus(booking_id, status);
			}

			bool HotelManager::updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out) {
				return bookings_manager.updateBookingDates(booking_id, check_in, check_out);
			}

			optional<Room> HotelManager::addNewRoom(const string& type, const string& status, double price) {
				return rooms_manager.addNewRoom(type, status, price);
			}

			optional<Customer> HotelManager::addNewCustomer(const string& name, int age, const string& phone, const string& email) {
				return customers_manager.addNewCustomer(name, age, phone, email);
			}

			optional<Booking> HotelManager::addNewBooking(const string& date, int days, int customer_id, int room_number) {
				if (doesRoomExist(room_number) == 0 || doesCustomerExist(customer_id) == 0) {
					return nullopt;
				}
				DateTime check_in;
				check_in.setDateAtNoon(date);
				DateTime check_out(check_in + days);
				auto room = getRoomByNumber(room_number);

				return bookings_manager.addNewBooking(customer_id, room_number, room->getPrice(), check_in, check_out);
			}

			bool HotelManager::deleteRoom(int room_number) {
				return getRoomsManager().deleteRoom(room_number);
			}

			bool HotelManager::deleteCustomer(int customer_id) {
				return getCustomersManager().deleteCustomer(customer_id);
			}

			bool HotelManager::deleteBooking(int booking_id) {
				return getBookingsManager().deleteBooking(booking_id);
			}
	
	//HotelUI
	
		// Private Function Definition
		HotelManager& HotelUI::getHotelManager() const {
			return hotel_manager;
		}

		// Constructor Definitions
		HotelUI::HotelUI(HotelManager& manager) : hotel_manager(manager) {}

		// Public Function Definition
		void HotelUI::printAvailableRoomsUI(const DateTime& chin, const DateTime& chout) const {
			auto available_rooms = getHotelManager().getAvailableRooms(chin, chout);
			cout << "\n\t\t=== Available Rooms ===\n";

			for (const auto& room : available_rooms) {
				room.printRoomDetails();
			}
			cout << '\n';
		}

		void HotelUI::printAllRoomsUI() const {
			cout << "\n\t\t=== All Rooms ===\n\n";

			auto rooms = getHotelManager().getAllRooms();
			for (const auto& room : rooms) {
				room.printRoomDetails();
			}
		}

		void HotelUI::printAllCustomersUI() const {
			cout << "\n\t\t=== All Customers ===\n\n";

			auto customers = getHotelManager().getAllCustomers();
			for (const auto& customer : customers) {
				customer.printCustomerData();
			}
		}

		void HotelUI::printAllBookingsUI() const {
			cout << "\n\t\t=== All Bookings ===\n\n";

			auto bookings = getHotelManager().getAllBookings();
			for (const auto& booking : bookings) {
				booking.printBookingData();
			}
		}

		void HotelUI::printRoomByNumberUI() const {
			int room_number = getValidatedInt("\t\tEnter Room number: ");
			if (auto room = getHotelManager().getRoomByNumber(room_number)) {
				cout << "\n\t\t=== Room Details ===\n";
				room->printRoomDetails();
			}
			else {
				cout << "\n\t\tError!!  Room doesn't Exist\n";
			}
		}

		void HotelUI::printCustomerByIdUI() const {
			int customer_id = getValidatedInt("\t\tEnter Customer ID: ");
			if (auto customer = getHotelManager().getCustomerById(customer_id)) {
				cout << "\n\t\t=== Customer Details ===\n";
				customer->printCustomerData();
			}
			else {
				cout << "\n\t\tError!!  Customer doesn't Exist\n";
			}
		}

		void HotelUI::printBookingByIDUI() const {
			int booking_number = getValidatedInt("\t\tEnter Booking ID: ");
			if (auto booking = getHotelManager().getBookingById(booking_number)) {
				cout << "\n\t\t=== Booking Details ===\n\n";
				booking->printBookingData();
			}
			else {
				cout << "\n\t\tError!!  Booking doesn't Exist\n";
			}
		}

		void HotelUI::addNewRoomUI() {
			cout << "\t\t=== Add New Room ===\n\n";

			string type;
			cout << "\t\t\tEnter room type(Single, Deluxe,Suite): ";
			cin >> type;
			double price = getValidatedDouble("\t\t\tEnter price: ");
			string status;
			cout << "\t\t\tEnter room status(Available, Maintenance): ";
			cin >> status;
			if (auto new_room = getHotelManager().addNewRoom(type, status, price)) {
				cout << "\n\t\tRoom is added successfully!\n\n";
				cout << "\t\tRoom Details:\n\n";
				new_room->printRoomDetails();
			}
			else cout << "\n\t\t\t Failed to add room!\n\n";
		}

		void HotelUI::addNewCustomerUI() {
			cout << "\t\t=== Add New Customer ===\n\n";

			string name;
			cout << "\t\t\tEnter customer name: ";
			cin >> name;
			int age = getValidatedInt("\t\t\tEnter age: ");
			string phone_number;
			cout << "\t\t\tEnter phone number: ";
			cin >> phone_number;
				string email;
				cout << "\t\t\tEnter email: ";
				cin >> email;
			try {
				if (auto new_customer = getHotelManager().addNewCustomer(name, age, phone_number, email)) {
					cout << "\n\t\tCustomer is added successfully!\n\n";
					cout << "\t\tCustomer Details:\n\n";
					new_customer->printCustomerData();
				}
				else cout << "\n\t\tFailed to add customer!\n\n";
				}
			catch (const invalid_argument& e) {
				cout << "\n\t\t" << e.what() << "\n\n";
			}
			catch (const std::exception& e) {
				// Catch any other standard exceptions
				cout << "\n\t\tAn error occurred: " << e.what() << "\n\n";
			}

		}

		void HotelUI::addNewBookingUI() {
			cout << "\n\t\t=== Add New Booking ===\n\n";

			string date;
			cout << "\n\t\t\tEnter Check-In date(YYYY-MM-DD): ";
			cin >> date;
			int days = getValidatedInt("\t\t\tEnter number of staying days: ");
			DateTime check_in;
			check_in.setDateAtNoon(date);
			DateTime check_out(check_in + days);
			int  customer_id = getValidatedInt("\n\t\t\tEnter Customer Id: ");
			while (getHotelManager().doesCustomerExist(customer_id) == false) {
				cout << "\n\t\t\tCustomer doesn't exist!\n";
				customer_id = getValidatedInt("\n\t\t\tEnter Customer Id: ");
			}
			printAvailableRoomsUI(check_in, check_out);
			int room_number;
			while (true) {
				room_number = getValidatedInt("\n\t\t\tEnter room number: ");

				if (getHotelManager().doesRoomExist(room_number) == false) {
					cout << "\n\t\tRoom doesn't exist!\n";
					continue;
				}
				if (getHotelManager().isRoomAvailableForDate(room_number, check_in, check_out, -1) == false) {
					cout << "\n\t\tRoom is not available for those dates!\n";
					continue;
				}
				//if both conditions are valid;
				break;
			}
			try {
				if (auto new_booking = getHotelManager().addNewBooking(date, days, customer_id, room_number)) {
					cout << "\n\t\tBooking is added successfully!\n\n";
					cout << "\t\tBooking Details:\n\n";
					new_booking->printBookingData();
				}
				else {
					cout << "\n\t\tFailed to add Booking!\n\n";
				}
			}
			catch(const invalid_argument&e) {
				cout << "\n\t\t" << e.what() << "\n\n";
			}
		}

		void HotelUI::deleteRoomUI() {
			int room_number = getValidatedInt("\t\t\tEnter room number: ");
			if (getHotelManager().doesRoomExist(room_number)) {
				if (getHotelManager().deleteRoom(room_number)) {
					cout << "\n\t\tRoom is deleted successfully\n\n";
				}
				else {
					cout << "\n\t\tFailed to delete Room\n\n";
				}
			}
			else {
				cout << "\n\t\tError!!  Room doesn't Exist\n";
			}
		}

		void HotelUI::deleteCustomerUI() {
			int customer_id = getValidatedInt("\n\t\tEnter customer ID: ");
			if (getHotelManager().doesCustomerExist(customer_id)) {
				if (getHotelManager().deleteCustomer(customer_id)) {
					cout << "\n\t\tCustomer is deleted successfully\n\n";
				}
				else {
					cout << "\n\t\tFailed to delete customer\n\n";
				}
			}
			else {
				cout << "\n\t\tError!!  Customer doesn't Exist\n";
			}
		}

		void HotelUI::deleteBookingUI() {
			int booking_id = getValidatedInt("\n\t\tEnter booking number: ");
			if (getHotelManager().doesBookingExist(booking_id)) {
				if (getHotelManager().deleteBooking(booking_id)) {
					cout << "\n\t\tBooking is deleted successfully\n\n";
				}
				else {
					cout << "\n\t\tFailed to delete Booking\n\n";
				}
			}
			else {
				cout << "\n\t\tError!!  Booking doesn't Exist\n";
			}
		}

		void HotelUI::modifyRoomUI() {
			int room_number = getValidatedInt("\t\t\tEnter Room Number: ");

			if (getHotelManager().doesRoomExist(room_number) == false) {
				cout << "\n\t\tERROR!!  Room doesn't Exist";
				return;
			}
			vector<string>available_choices = { "Change price per night","Change room type","Change room status","Finish updating" };
			string menu_name = "Room Update Menu";

			int choice = 0;
			do {
				choice = showOuterReadMenu(menu_name, available_choices);
				if (choice == 1) {
					double price = getValidatedDouble("\t\t\tEnter price per night: ");
					if (getHotelManager().updateRoomPrice(room_number, price))
						cout << "\n\t\tPrice updated successfully!\n";
					else
						cout << "\n\t\tFailed to update price!\n";
				}
				else if (choice == 2) {
					string type;
					cout << "\t\t\tEnter room type(Single, Double, Deluxe): ";
					cin >> type;
					if (getHotelManager().updateRoomType(room_number, type))
						cout << "\n\t\tType updated successfully!\n";
					else
						cout << "\n\t\tFailed to update type\n";
				}
				else if (choice == 3) {
					string status;
					cout << "\n\t\t\tEnter room status(Available, Booked, Maintenance): ";
					cin >> status;
					if (getHotelManager().updateRoomStatus(room_number, status)) {
						cout << "\n\t\tStatus updated successfully!\n";
					}
					else
						cout << "\n\t\tFailed to update Status!\n";
				}
			} while (choice != 4);
			cout << "\n\t\tRoom details after update:\n";
			optional<Room>room = getHotelManager().getRoomByNumber(room_number);
			room->printRoomDetails();
			cout << '\n';
		}

		void HotelUI::modifyCustomerUI() {
			int customer_id = getValidatedInt("\t\t\tEnter Customer ID: ");

			if (getHotelManager().doesCustomerExist(customer_id) == false) {
				cout << "\n\t\tERROR!!  Customer doesn't Exist\n\n";
				return;
			}
			vector<string>available_choices = { "Change Phone number","Change Email","Finish Updating" };
			string menu_name = "Customer Update Menu";

			int choice = 0;
			do {
					choice = showInnerReadMenu(menu_name, available_choices);
					if (choice == 1) {
						string phone;
						cout << "\t\t\tEnter Phone number: ";
						cin >> phone;
						try {
							if (getHotelManager().updateCustomerPhone(customer_id, phone))
								cout << "\n\t\tPhone Number updated successfully!\n";
							else
								cout << "\n\t\t Failed to update phone number!\n";
						}
						catch (const invalid_argument& e) {
							cout << "\n\t\t" << e.what() << "\n\n";
						}
					}
					else if (choice == 2) {
						string email;
						cout << "\t\t\tEnter Email: ";
						cin >> email;
						try{
						if (getHotelManager().updateCustomerEmail(customer_id, email))
							cout << "\n\t\tEmail updated successfully!\n";
						else
							cout << "\n\t\tFailed to update email!\n";
						}
						catch (const  invalid_argument& e) {
							cout << "\n\t\t" << e.what() << "\n\n";
						}
				}
				
			} while (choice != 3);
			cout << "\n\t\tCustomer  data after update:\n\n";
			optional<Customer> customer = getHotelManager().getCustomerById(customer_id);
			customer->printCustomerData();
			cout << '\n';
		}

		void HotelUI::modifyBookingUI() {
			int booking_id = getValidatedInt("\t\t\tEnter Booking ID: ");
			if (getHotelManager().doesBookingExist(booking_id) == false) {
				cout << "\n\t\tERROR!!  Booking not found\n";
				return;
			}
			optional<Booking> booking = getHotelManager().getBookingById(booking_id);

			vector<string>available_choices = { "Change Room","Change Status","Change Check-In/Out" ,"Finish Updating" };
			string menu_name = "Booking Update Menu";
			int choice = 0;
			do {
				choice = showOuterReadMenu(menu_name, available_choices);
				if (choice == 1) {
					DateTime check_in = booking->getCheckIn();
					DateTime check_out = booking->getCheckOut();
					printAvailableRoomsUI(check_in, check_out);
					int new_room_number = getValidatedInt("\t\t\tEnter Room number: ");
					if (getHotelManager().doesRoomExist(new_room_number) == 0) {
						cout << "\nError!! Room not found\n\n";
					}
					else {
						try {
							if (getHotelManager().updateBookingRoom(booking_id, new_room_number))
								cout << "\n\t\tRoom changed successfully!\n";
							else
								cout << "\n\t\tFailed to update room!\n";
						}
						catch (const invalid_argument& e) {
							cout << "\n\t\t" << e.what() << "\n\n";
						}
					}
				}
				else if (choice == 2) {
					string status;
					cout << "\t\t\tEnter Status: ";
					cin >> status;
					try {
						if (getHotelManager().updateBookingStatus(booking_id, status))
							cout << "\n\t\tStatus changed successfully!\n";
						else
							cout << "\n\t\t Failed to update status!\n";
					}
					catch (const invalid_argument& e) {
						cout << "\n\t\t" << e.what() << "\n\n";
					}
				}
				else if (choice == 3) {
					string date;
					cout << "\t\t\tEnter Check-In date(YYYY-MM-DD): ";
					cin >> date;
					int days = getValidatedInt("\t\t\tEnter number of staying days: ");

					DateTime check_in(date);
					DateTime check_out = check_in + days;
					int room_number = booking->getRoomNumber();
					if (getHotelManager().isRoomAvailableForDate(room_number, check_in, check_out, booking->getId()) == false) {
						cout << "\n\t\tRoom is not Available, Enter another room number\n";
					}
					else {
						try {
							if (getHotelManager().updateBookingDates(booking_id, check_in, check_out))
								cout << "\n\t\tCheck-In/Out changed successfully\n";
							else cout << "\n\t\tFailed to update Check-In/Out!\n";
						}
						catch (const invalid_argument& e) {
							cout << "\n\t\t" << e.what() << "\n\n";
						}
					}
				}
			} while (choice != 4);
			cout << "\n\t\tBooking  details after update:\n\n";
			auto  booking_after_update = getHotelManager().getBookingById(booking_id);
			booking_after_update->printBookingData();
			cout << '\n';
		}

	//HotelSystem
	// Private Function Definition
	HotelUI& HotelSystem::getHotelUI() {
		return hotel_ui;
	}

	HotelManager& HotelSystem::getHotelManager() {
		return hotel_manager;
	}

	void HotelSystem::showAdminRoomManagement() {
		vector<string>menu_items = {
			"Add New Room",
			"Delete Room",
			"Modify Room Details",
			"View Room Details",
			"View All Rooms",
			"Back to last Menu"
		};
		while (true) {
			int choice = showInnerReadMenu("ROOMS MANAGEMENT", menu_items);
			switch (choice) {
			case 1: getHotelUI().addNewRoomUI(); break;
			case 2: getHotelUI().deleteRoomUI(); break;
			case 3: getHotelUI().modifyRoomUI(); break;
			case 4: getHotelUI().printRoomByNumberUI(); break;
			case 5: getHotelUI().printAllRoomsUI(); break;
			case 6:return;
			}
		}
	}

	void HotelSystem::showReceptionistRoomOperations() {
		vector<string> menu_items = {
			"View All Rooms",
			"View Room Details",
			"View  Available Rooms",
			"Back to previouse Menu"
		};

		while (true) {
			int choice = showInnerReadMenu("ROOM INFORMATION", menu_items);

			switch (choice) {
			case 1:
				getHotelUI().printAllRoomsUI();
				break;

			case 2:
				getHotelUI().printRoomByNumberUI();
				break;

			case 3: {
				string date;
				cout << "\t\tEnter check-in date (YYYY-MM-DD): ";
				cin >> date;
				int days = getValidatedInt("\t\tEnter number of staying days:");
				DateTime check_in(date);
				DateTime check_out(check_in + days);
				getHotelUI().printAvailableRoomsUI(check_in, check_out);
				break;
			}
			case 4:
				return;
			}
		}
	}

	void HotelSystem::showCustomerManagementMenu() {
		vector<string> menu_items = {
			"Add New Customer",
			"Delete Customer",
			"Update Customer Information",
			"View Customer Details",
			"View All Customer",
			"Back to previouse Menu"
		};

		while (true) {
			int choice = showInnerReadMenu("CUSTOMERS MANAGEMENT", menu_items);

			switch (choice) {
			case 1: getHotelUI().addNewCustomerUI(); break;
			case 2: getHotelUI().deleteCustomerUI(); break;
			case 3: getHotelUI().modifyCustomerUI(); break;
			case 4: getHotelUI().printCustomerByIdUI(); break;
			case 5: getHotelUI().printAllCustomersUI(); break;
			case 6: return;
			}
		}
	}

	void HotelSystem::showBookingManagementMenu() {
		vector<string> menu_items = {
			"Create Booking",
			"Cancel Booking",
			"Modify Booking",
			"View Booking Details",
			"View All Bookings",
			"Back to previouse Menu"
		};

		while (true) {
			int choice = showInnerReadMenu("BOOKINGS MANAGEMENT", menu_items);

			switch (choice) {
			case 1: getHotelUI().addNewBookingUI(); break;
			case 2: getHotelUI().deleteBookingUI(); break;
			case 3: getHotelUI().modifyBookingUI(); break;
			case 4: getHotelUI().printBookingByIDUI(); break;
			case 5: getHotelUI().printAllBookingsUI(); break;
			case 6: return;
			}
		}
	}

	void HotelSystem::showAdminMenu() {
		vector<string>menu_items = {
			"Rooms Management",
			"Back to Main Menu" };
		while (true) {
			int choice = showOuterReadMenu("ADMIN MENU", menu_items);
			switch (choice) {
			case 1:showAdminRoomManagement(); break;
			case 2:return;
			}
		}
	}

	void HotelSystem::showReceptionistMenu() {
		vector<string>menu_items = {
			"Bookings Management",
			"Customers Management",
			"Rooms Information",
			"Back to Main Menu" };
		while (true) {
			int choice = showOuterReadMenu("RECEPTIONIST MENU", menu_items);
			switch (choice) {
			case 1:showBookingManagementMenu(); break;
			case 2:showCustomerManagementMenu(); break;
			case 3:showReceptionistRoomOperations(); break;
			case 4:return;
			}
		}
	}

	bool HotelSystem::checkPassword(const string& role) {
		string password;
		cout << "\n\t\tEnter " << role << " password: ";
		cin >> password;
		if (role == "admin")
			return password == "admin";
		else
			return password == "reception";
	}

	void HotelSystem::showMainMenu() {
		vector<string>menu_items = {
			"View Admin Menu",
			"View Receptionist Menu",
			"Exit" };
		while (true) {
			int choice = showOuterReadMenu("MAIN MENU", menu_items);
			switch (choice) {
			case 1:
				if (checkPassword("admin")) {
					showAdminMenu();
				}
				else {
					cout << "\n\t\tInvalid admin password!\n";
				}
				break;
			case 2:
				if (checkPassword("reception"))
					showReceptionistMenu();
				else
					cout << "\n\t\tInvalid receptionist password!\n";
				break;
			case 3:
				cout << "\n\t\tThank you for using the system!\n";
				return;
			}
		}
	}
	//Constructor Definition
	HotelSystem::HotelSystem() : hotel_ui(hotel_manager) {}
	// Public Function Definition
	void HotelSystem::run() {
		showMainMenu();
	}

int main() {
	HotelSystem system;
	system.run();
}