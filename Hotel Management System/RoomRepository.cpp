#include "RoomRepository.h"
#include "Suite.h"
#include "ScopedTransaction.h"
//Private Functions Definition
std::unique_ptr<Room> RoomRepository::createRoomFromRow(const IGenericResultSet& result)const {
	int room_number = result.getInt("room_number");
	std::string status = result.getString("status");
	std::string type = result.getString("room_type");
	double base_price = result.getDouble("base_price");
	if (type == "standard") {
		return std::make_unique<StandardRoom>(room_number, base_price, status);
	}
	else if (type == "deluxe") {
		double extra_fees = result.getDouble("extra_fees");
		return std::make_unique<DeluxeRoom>(room_number, base_price, status, extra_fees);
	}
	else if (type == "suite") {
		bool has_jacuzzi = result.getBoolean("has_jacuzzi");
		double jacuzzi_cost = result.getDouble("jacuzzi_cost");
		return std::make_unique<Suite>(room_number, base_price, status, has_jacuzzi, jacuzzi_cost);
	}
	throw std::runtime_error("Database Error: couldn't create room from row!");
}

int RoomRepository::addBaseRoomAndGetId(const Room& room) {
	if (!database.isTransactionActive()) {
		throw std::logic_error("addBaseRoomAndGetId function must be called within a transaction");
	}

	auto stmt = database.prepareStatement(
		"INSERT INTO rooms (room_type, status, base_price) VALUES (?, ?, ?)");
	stmt->setString(1, room.getType());
	stmt->setString(2, room.getStatus());
	stmt->setDouble(3, room.getBasePrice());
	stmt->executeUpdate();
	return database.getLastInsertID();
}

void RoomRepository::validateRoomExists(int room_number)const {
	auto stmt = database.prepareStatement("SELECT 1 FROM rooms WHERE room_number=? FOR UPDATE");
	stmt->setInt(1, room_number);
	auto result = stmt->executeQuery();
	if (!result->next()) {
		throw std::runtime_error("Database Error: Room " + std::to_string(room_number) + " doesn't exist!");
	}
}
std::vector<std::unique_ptr<Room>> RoomRepository::fetchRooms(std::unique_ptr<IGenericResultSet>result)const {
	std::vector<std::unique_ptr<Room>>rooms;
	while (result->next()) {
		rooms.emplace_back(createRoomFromRow(*result));
	}
	return rooms;
}

//Constructors Definition
RoomRepository::RoomRepository(IDatabase& db) :database(db) {}

//Public Functions Definition

int RoomRepository::addStandardRoom(const StandardRoom& standard_room) {
		ScopedTransaction transaction(database);
		int room_number=addBaseRoomAndGetId(standard_room);
		transaction.commit();
		return room_number;
}

int RoomRepository::addDeluxeRoom(const DeluxeRoom& deluxe_room) {

		ScopedTransaction transaction(database);
		int room_number = addBaseRoomAndGetId(deluxe_room);
		auto stmt = database.prepareStatement("UPDATE rooms SET extra_fees = ? WHERE room_number=?");
		stmt->setDouble(1, deluxe_room.getExtraFees());
		stmt->setInt(2, room_number);
		stmt->executeUpdate();
		transaction.commit();
		return room_number;
	
}
int RoomRepository::addSuite(const Suite& suite) {
		ScopedTransaction transaction(database);

		int room_number = addBaseRoomAndGetId(suite);
		auto stmt = database.prepareStatement("UPDATE rooms SET has_jacuzzi= ? ,jacuzzi_cost = ? WHERE room_number=?");
		stmt->setBoolean(1, suite.hasJacuzzi());
		stmt->setDouble(2, suite.getJacuzziCost());
		stmt->setInt(3, room_number);
		stmt->executeUpdate();

		transaction.commit();
		return room_number;
}

int RoomRepository::getNumberOfRooms()const {
	auto stmt = database.prepareStatement("SELECT COUNT(*) FROM rooms");
	auto result = stmt->executeQuery();
	return result->next() ? result->getInt(1) : 0;
}
std::unique_ptr<Room>RoomRepository::getRoomByNumber(int room_num)const {
	auto stmt = database.prepareStatement("SELECT * FROM rooms WHERE room_number=?");
	stmt->setInt(1, room_num);
	auto result = stmt->executeQuery();
	if (!result->next()) {
		throw std::runtime_error("Room " + std::to_string(room_num) + " not found!");
	}
	return createRoomFromRow(*result);
}

std::vector<std::unique_ptr<Room>> RoomRepository::getRoomsByStatus(const std::string& status)const {
	auto stmt = database.prepareStatement("SELECT * FROM rooms WHERE status=?");
	stmt->setString(1, status);
	auto result = stmt->executeQuery();
	auto rooms = fetchRooms(std::move(result));
	return rooms;
}
std::vector<std::unique_ptr<Room>> RoomRepository::getRoomsByType(const std::string& type)const {
	auto stmt = database.prepareStatement("SELECT * FROM rooms WHERE room_type=?");
	stmt->setString(1, type);
	auto result = stmt->executeQuery();
	auto rooms = fetchRooms(std::move(result));
	return rooms;
}


std::vector<std::unique_ptr<Room>>RoomRepository::getAllRooms()const {
	auto stmt = database.prepareStatement("SELECT * FROM rooms");
	auto result = stmt->executeQuery();
	return fetchRooms(std::move(result));
}

void RoomRepository::updateRoomPrice(int room_num, double new_price) {
	ScopedTransaction transaction(database);

	validateRoomExists(room_num);
	auto stmt = database.prepareStatement("UPDATE rooms SET base_price=? WHERE room_number=?");
	stmt->setDouble(1, new_price);
	stmt->setInt(2, room_num);
	stmt->executeUpdate();

	transaction.commit();
}
void RoomRepository::updateRoomStatus(int room_num, const std::string& status) {
	ScopedTransaction transaction(database);

		validateRoomExists(room_num);
		auto stmt = database.prepareStatement("UPDATE rooms SET status=? WHERE room_number=?");
		stmt->setString(1, status);
		stmt->setInt(2, room_num);
		stmt->executeUpdate();

		transaction.commit();
}

void RoomRepository::deleteRoom(int room_num) {
	ScopedTransaction transaction(database);

		validateRoomExists(room_num);
		auto stmt = database.prepareStatement("DELETE FROM rooms WHERE room_number=?");
		stmt->setInt(1, room_num);
		stmt->executeUpdate();

		transaction.commit();
}