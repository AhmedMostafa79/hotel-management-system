#include "BookingRepository.h"


// Private helper methods
Booking BookingRepository::createBookingFromRow(const IGenericResultSet& result) const {
    return Booking(
        result.getInt("booking_id"),
        result.getInt("room_number"),
        result.getInt("customer_id"),
        result.getDouble("cost"),
        DateTime(result.getString("check_in")),
        DateTime(result.getString("check_out")),
        result.getString("status")
    );
}

std::vector<Booking> BookingRepository::fetchBookings(std::unique_ptr<IGenericResultSet> result) const {
    std::vector<Booking> bookings;
    while (result->next()) {
        bookings.emplace_back(createBookingFromRow(*result));
    }
    return bookings;
}

void BookingRepository::validateBookingExists(int booking_id) const {
    if (!doesBookingExist(booking_id)) {
        throw std::runtime_error("Database Error: Booking " + std::to_string(booking_id) + " doesn't exist!");
    }
}
int BookingRepository::getLastInsertedId()const {
    auto stmt = database.prepareStatement("SELECT LAST_INSERT_ID()");
    auto result = stmt->executeQuery();
    if (result->next()) {
        return result->getInt(1);
    }
    throw std::runtime_error("Database Error: Failed to get last inserted booking id");
}

// Constructor
BookingRepository::BookingRepository(IDatabase& db) : database(db) {}

// Public methods
bool BookingRepository::doesBookingExist(int booking_id) const {
    auto stmt = database.prepareStatement("SELECT COUNT(*) FROM bookings WHERE booking_id = ?");
    stmt->setInt(1, booking_id);
    auto result = stmt->executeQuery();
    return result->next() && result->getInt(1) > 0;
}

// CREATE
int BookingRepository::addBooking(const Booking& booking) {
    try {
        auto stmt = database.prepareStatement(
            "INSERT INTO bookings(room_number, customer_id, check_in, check_out, cost, status) VALUES (?,?,?,?,?,?)"
        );
        stmt->setInt(1, booking.getRoomNumber());
        stmt->setInt(2, booking.getCustomerId());
        stmt->setString(3, booking.getCheckIn().getDateTimeString());
        stmt->setString(4, booking.getCheckOut().getDateTimeString());
        stmt->setDouble(5, booking.getCost());
        stmt->setString(6, booking.getStatus());
        stmt->executeUpdate();
        return getLastInsertedId();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Database Error: Failed to add booking: " + std::string(e.what()));
    }
}

// READ
Booking BookingRepository::getBookingById(int booking_id) const {
    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("SELECT * FROM bookings WHERE booking_id = ?");
    stmt->setInt(1, booking_id);
    auto result = stmt->executeQuery();
    if (result->next()) return createBookingFromRow(*result);
    throw std::runtime_error("Database Error: Booking " + std::to_string(booking_id) + " not found!");
}

int BookingRepository::getNumberOfBookings() const {
    auto stmt = database.prepareStatement("SELECT COUNT(*) FROM bookings");
    auto result = stmt->executeQuery();
    return result->next() ? result->getInt(1) : 0;
}

std::vector<Booking> BookingRepository::getAllBookings() const {
    auto stmt = database.prepareStatement("SELECT * FROM bookings");
    auto result = stmt->executeQuery();
    return fetchBookings(std::move(result));
}

std::vector<Booking> BookingRepository::getBookingsByRoom(int room_num) const {
    auto stmt = database.prepareStatement("SELECT * FROM bookings WHERE room_number = ?");
    stmt->setInt(1, room_num);
    auto result = stmt->executeQuery();
    return fetchBookings(std::move(result));
}

// UPDATE
void BookingRepository::updateBookingStatus(int booking_id, const std::string& status) {
    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("UPDATE bookings SET status = ? WHERE booking_id = ?");
    stmt->setString(1, status);
    stmt->setInt(2, booking_id);
    stmt->executeUpdate();
}

void BookingRepository::updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out) {
    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("UPDATE bookings SET check_in = ?, check_out = ? WHERE booking_id = ?");
    stmt->setString(1, check_in.getDateTimeString());
    stmt->setString(2, check_out.getDateTimeString());
    stmt->setInt(3, booking_id);
    stmt->executeUpdate();
}

// DELETE
void BookingRepository::deleteBooking(int booking_id) {
    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("DELETE FROM bookings WHERE booking_id = ?");
    stmt->setInt(1, booking_id);
    if (!stmt->executeUpdate()) {
        throw std::runtime_error("Database Error: Failed to delete booking: " + std::to_string(booking_id));
    }
}
