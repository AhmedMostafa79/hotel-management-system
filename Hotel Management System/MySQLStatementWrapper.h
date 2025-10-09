#pragma once
#include "IGenericStatement.h"
#include "MySQLResultSetWrapper.h"
#include <cppconn/prepared_statement.h>
#include <memory>

/**
 * @file MySQLStatementWrapper.h
 * @brief Adapter that wraps a MySQL Connector/C++ prepared statement.
 *
 * The wrapper holds the native `sql::PreparedStatement` and exposes the
 * IGenericStatement interface so repository code can bind parameters and
 * execute statements without depending on the MySQL driver API.
 */
class MySQLStatementWrapper : public IGenericStatement {
    std::unique_ptr<sql::PreparedStatement> stmt; ///< Owned driver prepared statement
public:
    /**
     * @brief Construct wrapper and take ownership of the provided native statement.
     * @param statement Raw pointer to a driver prepared statement; ownership is transferred.
     */
    MySQLStatementWrapper(sql::PreparedStatement* statement);

    MySQLStatementWrapper(std::unique_ptr<sql::PreparedStatement>) = delete;
    MySQLStatementWrapper(const MySQLStatementWrapper&) = delete;
    MySQLStatementWrapper& operator=(const MySQLStatementWrapper&) = delete;

    /**
     * @brief Bind an integer parameter to the prepared statement.
     * @param paramIndex 1-based parameter index.
     * @param value Integer value to bind.
     * @throws std::runtime_error on driver errors.
     */
    void setInt(int paramIndex, int value) override;

    /**
     * @brief Bind a string parameter to the prepared statement.
     * @param paramIndex 1-based parameter index.
     * @param value String value to bind.
     * @throws std::runtime_error on driver errors.
     */
    void setString(int paramIndex, const std::string& value) override;

    /**
     * @brief Bind a double parameter to the prepared statement.
     * @param paramIndex 1-based parameter index.
     * @param value Double value to bind.
     * @throws std::runtime_error on driver errors.
     */
    void setDouble(int paramIndex, double value) override;

    /**
     * @brief Bind a boolean parameter to the prepared statement.
     * @param paramIndex 1-based parameter index.
     * @param value Boolean value to bind.
     * @throws std::runtime_error on driver errors.
     */
    void setBoolean(int paramIndex, bool value) override;

    /**
     * @brief Execute a statement that may return either a result set or no results.
     * @return true if the execution produced a result set, false otherwise.
     * @throws std::runtime_error on driver errors.
     */
    bool execute() override;

    /**
     * @brief Execute a DML statement (INSERT/UPDATE/DELETE) and return affected rows.
     * @return Number of rows affected by the statement.
     * @throws std::runtime_error on driver errors.
     */
    int executeUpdate() override;

    /**
     * @brief Execute a query that returns a result set.
     * @return A unique_ptr owning an `IGenericResultSet` that wraps the native result.
     * @throws std::runtime_error on driver errors.
     */
    std::unique_ptr<IGenericResultSet> executeQuery() const override;

    /**
     * @brief Clear any previously bound parameters on the prepared statement.
     * @throws std::runtime_error on driver errors.
     */
    void clearParameters() override;
};
