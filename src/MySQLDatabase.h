#pragma once
#include "IDatabase.h"
#include "MySQLStatementWrapper.h"
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <memory>
#include <stdexcept>
#include "DatabaseConfig.h"

/**
 * @file MySQLDatabase.h
 * @brief MySQL-specific implementation of the IDatabase adapter.
 *
 * This class uses the MySQL Connector/C++ driver to manage connections and
 * prepare statements. It adapts driver-specific connection and statement
 * objects to the project's generic interfaces (IGenericStatement /
 * IGenericResultSet).
 */
class MySQLDatabase : public IDatabase {
private:
    std::unique_ptr<sql::Connection> connection; ///< Owning pointer to the driver connection.
    bool transactionActive;
    /**
     * @brief Returns a raw pointer to the driver connection.
     * @return sql::Connection* Raw connection pointer (may be null).
     */
    sql::Connection* getConnection() override;

protected:
    /**
     * @brief Close and release the driver connection.
     */
    void disconnect() override;

public:
    /**
     * @brief Default constructor.
     */
    MySQLDatabase();

    /**
     * @brief Connect to a MySQL server using the supplied configuration.
     * @param config Database connection parameters (schema/server/username/password).
     */
    void connect(const DatabaseConfig& config) override;

    /**
     * @brief Prepare a statement wrapper for a SQL query.
     * @param query SQL query string to prepare.
     * @return std::unique_ptr<IGenericStatement> Prepared statement adapter.
     */
    std::unique_ptr<IGenericStatement> prepareStatement(const std::string& query) override;

    /**
     * @brief Check whether a usable connection is established.
     * @return true if connected and the underlying connection is valid.
     */
    bool isConnected() const override;

    /**
     * @brief Return a human-friendly name for this implementation.
     * @return std::string Typically "MySQL".
     */
    std::string getType() const override;
    void beginTransaction()override;
     void commitTransaction() override;
     void rollbackTransaction() override;
     bool isTransactionActive() override { return transactionActive;}
     std::string getTransactionIsolationLevel() const override;
     void setTransactionIsolationLevel(const std::string& level) override;
     int getLastInsertID()  override;
    /**
     * @brief Destructor that ensures the connection is closed.
     */
    ~MySQLDatabase();
};
