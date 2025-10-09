#include "RoomRepository.h"
#include "Suite.h"
//Private Functions Definition
bool RoomRepository::doesRoomExist(int room_num)const {
	auto stmt = database.prepareStatement("SELECT COUNT(*) FROM rooms WHERE room_number=?");
	stmt->setInt(1, room_num);
	auto result = stmt->executeQuery();
	return result->next() && result->getInt(1) > 0;
}
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
	auto stmt = database.prepareStatement(
		"INSERT INTO rooms (room_type, status, base_price) VALUES (?, ?, ?)");
	stmt->setString(1, room.getType());
	stmt->setString(2, room.getStatus());
	stmt->setDouble(3, room.getBasePrice());
	if (stmt->executeUpdate() > 0) {
		return getLastInsertedId();//as we use AUTO_INCREMENT the last added id is the number of existing rooms.
	}
	throw std::runtime_error("Database Error: Failed to insert base room!");
}
int RoomRepository::getLastInsertedId()const {
	auto stmt = database.prepareStatement("SELECT LAST_INSERT_ID()");
	auto result = stmt->executeQuery();
	if (result->next()) {
		return result->getInt(1);
	}
	throw std::runtime_error("Database Error: Failed to get last inserted customer id");
}

void RoomRepository::validateRoomExists(int room_number)const {
	if (!doesRoomExist(room_number)) {
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
	try {
		return addBaseRoomAndGetId(standard_room);
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Database Error: Failed to Add Standard Room: " + std::string(e.what()));
	}
}

int RoomRepository::addDeluxeRoom(const DeluxeRoom& deluxe_room) {

	try {
		int room_number = addBaseRoomAndGetId(deluxe_room);
		auto stmt = database.prepareStatement("UPDATE rooms SET extra_fees = ? WHERE room_number=?");
		stmt->setDouble(1, deluxe_room.getExtraFees());
		stmt->setInt(2, room_number);
		stmt->executeUpdate();
		return room_number;
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Database Error: Failed to Add Deluxe Room: " + std::string(e.what()));
	}
}
int RoomRepository::addSuite(const Suite& suite) {
	try {
		int room_number = addBaseRoomAndGetId(suite);
		auto stmt = database.prepareStatement("UPDATE rooms SET has_jacuzzi= ? ,jacuzzi_cost = ? WHERE room_number=?");
		stmt->setBoolean(1, suite.hasJacuzzi());
		stmt->setDouble(2, suite.getJacuzziCost());
		stmt->setInt(3, room_number);
		stmt->executeUpdate();
		return room_number;
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Database Error: Failed to Add Suite: " + std::string(e.what()));
	}
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
		throw std::runtime_error("Database Error: Room " + std::to_string(room_num) + " not found!");
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
	validateRoomExists(room_num);
	auto stmt = database.prepareStatement("UPDATE rooms SET base_price=? WHERE room_number=?");
	stmt->setDouble(1, new_price);
	stmt->setInt(2, room_num);
	stmt->executeUpdate();
}
void RoomRepository::updateRoomStatus(int room_num, const std::string& status) {
	validateRoomExists(room_num);
	auto stmt = database.prepareStatement("UPDATE rooms SET status=? WHERE room_number=?");
	stmt->setString(1, status);
	stmt->setInt(2, room_num);
	stmt->executeUpdate();
}

void RoomRepository::deleteRoom(int room_num) {
	validateRoomExists(room_num);
	auto stmt = database.prepareStatement("DELETE FROM rooms WHERE room_number=?");
	stmt->setInt(1, room_num);
	if (!stmt->executeUpdate()) {
		throw std::runtime_error("Database Error: Failed to delete room: " + std::to_string(room_num));
	}
}