#pragma once

#include "IGenericStatement.h"
#include <memory>
#include <string>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h> // sql::Connection
#include "DatabaseConfig.h"

/**
 * @file IDatabase.h
 * @brief Abstract database adapter interface used by repository classes.
 *
 * The IDatabase interface abstracts a concrete database implementation
 * (for example MySQL) behind a minimal set of operations required by the
 * repository layer: connecting, preparing statements and checking
 * connection state. Concrete implementations own the underlying connection
 * object and translate prepare/execute calls into driver-specific code.
 */

/**
 * @class IDatabase
 * @brief Minimal database adapter interface.
 *
 * Implementations must manage a single connection and provide a way to
 * prepare generic statements (wrapping driver specific statements in the
 * IGenericStatement adapter). The interface is intentionally small to keep
 * the rest of the codebase independent from any particular database driver.
 */
class IDatabase {
protected:
   /**
    * @brief Disconnect the underlying connection.
    *
    * Implementations should close/cleanup the driver-specific connection
    * resource. This is protected because callers should normally use
    * the public lifecycle methods (connect/isConnected) instead of
    * directly disconnecting.
    */
   virtual void disconnect() = 0;

   /**
    * @brief Access the underlying driver connection object.
    *
    * Returns a raw pointer to the driver connection (sql::Connection for
    * the MySQL connector). This is primarily used by adapters or test code
    * that require low-level access.
    *
    * @return sql::Connection* Pointer to the driver connection (may be null).
    */
   virtual sql::Connection* getConnection() = 0;

public:
   virtual ~IDatabase() = default;

   /**
    * @brief Establish a connection using the supplied configuration.
    *
    * Implementations are free to throw on failure. The provided
    * DatabaseConfig contains all required parameters (schema, server,
    * username, password).
    *
    * @param config Configuration object describing the connection.
    */
   virtual void connect(const DatabaseConfig& config) = 0;

   /**
    * @brief Prepare a statement wrapper for the given SQL query.
    *
    * The returned IGenericStatement is an adapter around the driver
    * statement object and is used by repository code to execute queries
    * and read results without depending on the driver API.
    *
    * @param query SQL query string to prepare.
    * @return std::unique_ptr<IGenericStatement> Prepared statement wrapper.
    */
   virtual std::unique_ptr<IGenericStatement> prepareStatement(const std::string& query) = 0;

   /**
    * @brief Query the connection state.
    *
    * @return true When a usable connection is available.
    * @return false Otherwise.
    */
   virtual bool isConnected() const = 0;

   /**
    * @brief Human readable type name for the database implementation.
    *
    * Used for diagnostics/logging (for example "MySQL")
    *
    * @return std::string The implementation type name.
    */
   virtual std::string getType() const = 0;

   virtual void beginTransaction() = 0;
   virtual void commitTransaction() = 0;
   virtual void rollbackTransaction() = 0;
   virtual bool isTransactionActive() = 0;
   virtual std::string getTransactionIsolationLevel()const  = 0;
   virtual void setTransactionIsolationLevel(const std::string&level) = 0;
   virtual int getLastInsertID() = 0;
};
