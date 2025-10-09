#pragma once
#include "IGenericResultSet.h"
#include <memory>
#include <string>

/**
 * @file IGenericStatement.h
 * @brief Small adapter that abstracts driver-prepared-statement behavior.
 *
 * Repository code uses this interface to bind parameters and execute
 * statements without depending on a specific SQL driver API.
 */
class IGenericStatement {
public:
    virtual ~IGenericStatement() = default;

    /**
     * @brief Bind an integer parameter at the given 1-based index.
     * @param paramIndex 1-based parameter index.
     * @param value Integer value to bind.
     */
    virtual void setInt(int paramIndex, int value) = 0;

    /**
     * @brief Bind a string parameter at the given 1-based index.
     * @param paramIndex 1-based parameter index.
     * @param value String value to bind.
     */
    virtual void setString(int paramIndex, const std::string& value) = 0;

    /**
     * @brief Bind a double parameter at the given 1-based index.
     * @param paramIndex 1-based parameter index.
     * @param value Double value to bind.
     */
    virtual void setDouble(int paramIndex, double value) = 0;

    /**
     * @brief Bind a boolean parameter at the given 1-based index.
     * @param paramIndex 1-based parameter index.
     * @param value Boolean value to bind.
     */
    virtual void setBoolean(int paramIndex, bool value) = 0;

    /**
     * @brief Execute a statement that does not return a result set.
     * @return true on success, false otherwise.
     */
    virtual bool execute() = 0;

    /**
     * @brief Execute an update/insert/delete statement and return rows affected.
     * @return int Number of rows affected by the statement.
     */
    virtual int executeUpdate() = 0;

    /**
     * @brief Execute a query and obtain a result set.
     * @return std::unique_ptr<IGenericResultSet> Owned result set object.
     */
    virtual std::unique_ptr<IGenericResultSet> executeQuery() const = 0;

    /**
     * @brief Clear all previously bound parameters so the statement can be reused.
     */
    virtual void clearParameters() = 0;
};
