#pragma once
#include "Room.h"
#include "Suite.h"
#include "StandardRoom.h"
#include "DeluxeRoom.h"
#include <vector>
#include <memory>
#include <string>
#include "IDatabase.h"

/**
 * @file RoomRepository.h
 * @brief Persistence operations for Room entities.
 *
 * The RoomRepository implements CRUD operations for Room objects using the
 * provided IDatabase adapter. All methods operate on the underlying
 * database and translate rows into concrete Room subclasses.
 */
class RoomRepository {
	IDatabase& database; ///< Reference to the database adapter used for queries.

	/**
	 * @brief Helper: create a concrete Room instance from a result row.
	 * @param result Result row abstraction to read columns from.
	 * @return std::unique_ptr<Room> Owned pointer to the created Room.
	 */
	std::unique_ptr<Room> createRoomFromRow(const IGenericResultSet& result) const;

	/**
	 * @brief Insert the common base room fields and return the generated id.
	 * @param room Room object containing base fields to insert.
	 * @return int Newly inserted room id.
	 */
	int addBaseRoomAndGetId(const Room& room);

	/**
	 * @brief Helper: read last inserted id from the connection.
	 * @return int The last auto-increment id for the session.
	 */
	int getLastInsertedId() const;

	/**
	 * @brief Convert a driver result into a vector of Room pointers.
	 * @param result Owned result set returned from a query.
	 * @return std::vector<std::unique_ptr<Room>> Vector of owned Room objects.
	 */
	std::vector<std::unique_ptr<Room>> fetchRooms(std::unique_ptr<IGenericResultSet> result) const;

public:
	/**
	 * @brief Construct a RoomRepository using the given database adapter.
	 * @param db Adapter that performs the actual DB operations.
	 */
	RoomRepository(IDatabase& db);

	/**
	 * @brief Check if a room with the given number exists.
	 * @param room_num Room number to check.
	 * @return true if the room exists, false otherwise.
	 */
	bool doesRoomExist(int room_num) const;

	/**
	 * @brief Validate existence of a room and throw if not present.
	 * @param room_number Room number to validate.
	 * @throws std::invalid_argument if the room does not exist.
	 */
	void validateRoomExists(int room_number) const;

	// CREATE operations
	/**
	 * @brief Insert a StandardRoom and return its generated id.
	 * @param room StandardRoom object to insert.
	 * @return int Inserted record id.
	 */
	int addStandardRoom(const StandardRoom& room);

	/**
	 * @brief Insert a DeluxeRoom and return its generated id.
	 * @param room DeluxeRoom object to insert.
	 * @return int Inserted record id.
	 */
	int addDeluxeRoom(const DeluxeRoom& room);

	/**
	 * @brief Insert a Suite and return its generated id.
	 * @param suite Suite object to insert.
	 * @return int Inserted record id.
	 */
	int addSuite(const Suite& suite);

	// READ operations
	/**
	 * @brief Get the total number of rooms in storage.
	 * @return int Number of rooms.
	 */
	int getNumberOfRooms() const;

	/**
	 * @brief Retrieve all rooms.
	 * @return std::vector<std::unique_ptr<Room>> Owned list of rooms.
	 */
	std::vector<std::unique_ptr<Room>> getAllRooms() const;

	/**
	 * @brief Load a single room by its number.
	 * @param room_num Room number to load.
	 * @return std::unique_ptr<Room> Owned Room object.
	 */
	std::unique_ptr<Room> getRoomByNumber(int room_num) const;

	/**
	 * @brief Get rooms filtered by their status string.
	 * @param status Status to filter by (e.g. "available").
	 * @return std::vector<std::unique_ptr<Room>> Matching rooms.
	 */
	std::vector<std::unique_ptr<Room>> getRoomsByStatus(const std::string& status) const;

	/**
	 * @brief Get rooms filtered by type string.
	 * @param type Room type (e.g. "standard").
	 * @return std::vector<std::unique_ptr<Room>> Matching rooms.
	 */
	std::vector<std::unique_ptr<Room>> getRoomsByType(const std::string& type) const;

	// UPDATE operations
	/**
	 * @brief Update the base price for a given room.
	 * @param room_num Room number to update.
	 * @param new_price New price per night.
	 */
	void updateRoomPrice(int room_num, double new_price);

	/**
	 * @brief Update the status of a room (e.g. Available/Maintenance).
	 * @param room_num Room number to update.
	 * @param status New status string.
	 */
	void updateRoomStatus(int room_num, const std::string& status);

	// DELETE operations
	/**
	 * @brief Delete a room by its number.
	 * @param room_num Room number to remove.
	 */
	void deleteRoom(int room_num);

};