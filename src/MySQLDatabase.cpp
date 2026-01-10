#include "MySQLDatabase.h"
#include <cppconn/driver.h>
#include <cppconn/connection.h>

MySQLDatabase::MySQLDatabase():transactionActive(false){}
sql::Connection* MySQLDatabase::getConnection() {
    if (!isConnected()) {
        throw std::runtime_error("Database Error: MySQL database not connected! Call connect() first.");
    }
    return connection.get();
}

void MySQLDatabase::disconnect() {
    if (connection) {
        connection->close();
        connection.reset();
    }
}

void MySQLDatabase::connect(const DatabaseConfig& config) {
    try {
        auto driver = get_driver_instance();
        connection.reset(driver->connect(config.getServer(), config.getUsername(), config.getPassword()));
        connection->setSchema(config.getSchema());
    }
        catch (const std::exception& e) {
            throw std::runtime_error("Database Error: Connection failed: " + std::string(e.what()));
    }
}

std::unique_ptr<IGenericStatement> MySQLDatabase::prepareStatement(const std::string& query) {
    return std::make_unique<MySQLStatementWrapper>(getConnection()->prepareStatement(query));
}

bool MySQLDatabase::isConnected() const {
    return connection && !connection->isClosed();
}

std::string MySQLDatabase::getType() const { return "MySQL"; }


void MySQLDatabase::beginTransaction() {
    if (!isConnected()) {
        throw std::runtime_error("Cannot begin transaction: not connected to database");
    }
    if (transactionActive) {
        throw std::runtime_error("Transaction already active");
    }
    try {
        connection->setAutoCommit(false);
        transactionActive = true;
    }
    catch (const std::exception&e){
        throw std::runtime_error("Failed to begin transaction: " + std::string(e.what()));
    }
 }
void MySQLDatabase::commitTransaction() {
    if (!transactionActive) {
        throw std::runtime_error("No active transaction to commit");
    }
    try {
        connection->commit();
        connection->setAutoCommit(true);
        transactionActive = false;
    }
    catch (const std::exception& e) {
        try {
            connection->rollback();
            connection->setAutoCommit(true);
        }
        catch (...) {
            // Ignore rollback errors during commit failure
        }
        transactionActive = false;
        throw std::runtime_error("Failed to commit transaction: " + std::string(e.what()));
    }
 }
void MySQLDatabase::rollbackTransaction() {
    if (!transactionActive) {
        throw std::runtime_error("No active transaction to rollback");
    }
    try {
        connection->rollback();
        connection->setAutoCommit(true);
        transactionActive = false;
    }
    catch(const std::exception&e){
        transactionActive = false;
        throw std::runtime_error("Failed to rollback transaction: " + std::string(e.what()));
    }
 }

std::string MySQLDatabase::getTransactionIsolationLevel()const {
    if (!isConnected()) {
        throw std::runtime_error("Not connected to database");
    }
    try {
        auto stmt = connection->createStatement();
        auto result = stmt->executeQuery("SELECT @@transaction_isolation");
        if (result->next()) {
            return result->getString(1);
        }
        return "UNKNOWN";
    }
    catch(const std::exception&e){
        throw std::runtime_error("Failed to get isolation level: " + std::string(e.what()));
    }
 }
void MySQLDatabase::setTransactionIsolationLevel(const std::string& level) {
    if (!isConnected()) {
        throw std::runtime_error("Not connected to database");
    }
    try {
        std::string query= "SET SESSION TRANSACTION ISOLATION LEVEL " + level;
        auto stmt = connection->createStatement();
        stmt->execute(query);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to set isolation level '" + level + "': " + std::string(e.what()));
    }
 }
int MySQLDatabase::getLastInsertID() {
    auto idStmt = prepareStatement("SELECT LAST_INSERT_ID()");

    auto result = idStmt->executeQuery();
    if (result->next()) {
        return result->getInt(1);
    }
        throw std::runtime_error("Failed to get last inserted id");
}

MySQLDatabase::~MySQLDatabase() { disconnect(); }
