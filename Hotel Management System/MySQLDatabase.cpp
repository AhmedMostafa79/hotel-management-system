#include "MySQLDatabase.h"
#include <cppconn/driver.h>
#include <cppconn/connection.h>

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

MySQLDatabase::~MySQLDatabase() { disconnect(); }
