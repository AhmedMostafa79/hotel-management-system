#include "BookingRepository.h"
#include "ScopedTransaction.h"

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
    auto stmt = database.prepareStatement("SELECT 1 FROM bookings WHERE booking_id = ?");
    stmt->setInt(1, booking_id);
    auto result = stmt->executeQuery();
    if(!result->next()){
    throw std::runtime_error("Database Error: Booking " + std::to_string(booking_id) + " doesn't exist!");
    }
}

// Constructor
BookingRepository::BookingRepository(IDatabase& db) : database(db) {}

// Public methods


// CREATE
int BookingRepository::addBookingAndGetId(const Booking& booking) {
    ScopedTransaction transaction(database);

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
    int booking_id =database.getLastInsertID();
    transaction.commit();
    return booking_id;
}

// READ
Booking BookingRepository::getBookingById(int booking_id) const {
    auto stmt = database.prepareStatement("SELECT * FROM bookings WHERE booking_id = ?");
    stmt->setInt(1, booking_id);
    auto result = stmt->executeQuery();
    if (result->next()) {
        return createBookingFromRow(*result);
    }
    throw std::runtime_error("Booking " + std::to_string(booking_id) + " not found!");
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
    ScopedTransaction transaction(database);

    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("UPDATE bookings SET status = ? WHERE booking_id = ?");
    stmt->setString(1, status);
    stmt->setInt(2, booking_id);
    stmt->executeUpdate();

    transaction.commit();
}

void BookingRepository::updateBookingDates(int booking_id, const DateTime& check_in, const DateTime& check_out) {
    ScopedTransaction transaction(database);

    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("UPDATE bookings SET check_in = ?, check_out = ? WHERE booking_id = ?");
    stmt->setString(1, check_in.getDateTimeString());
    stmt->setString(2, check_out.getDateTimeString());
    stmt->setInt(3, booking_id);
    stmt->executeUpdate();

    transaction.commit();
}

// DELETE
void BookingRepository::deleteBooking(int booking_id) {
    ScopedTransaction transaction(database);

    validateBookingExists(booking_id);
    auto stmt = database.prepareStatement("DELETE FROM bookings WHERE booking_id = ?");
    stmt->setInt(1, booking_id);
    stmt->executeUpdate();

    transaction.commit();
}
