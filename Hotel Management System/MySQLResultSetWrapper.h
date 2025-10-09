#pragma once
#include "IGenericResultSet.h"
#include <cppconn/resultset.h>
#include <memory>
#include <stdexcept>

/**
 * @file MySQLResultSetWrapper.h
 * @brief Adapter wrapping MySQL Connector/C++ result sets into IGenericResultSet.
 *
 * The wrapper takes ownership of a raw `sql::ResultSet*` provided by the
 * driver and exposes a driver-agnostic interface used by repository code.
 */
class MySQLResultSetWrapper : public IGenericResultSet {
    std::unique_ptr<sql::ResultSet> result; ///< Owned driver result set
public:
    /**
     * @brief Construct the wrapper and assume ownership of the provided result pointer.
     *
     * The wrapper takes ownership of @p result_set and will free it when this
     * object is destroyed. Prefer passing the raw pointer returned by the
     * MySQL driver directly to this constructor; do not delete the pointer
     * afterwards.
     *
     * @param result_set Raw pointer returned by the driver. Ownership is
     *                   transferred to the wrapper and will be managed via
     *                   std::unique_ptr internally.
     * @throws std::invalid_argument if @p result_set is nullptr.
     */
    MySQLResultSetWrapper(sql::ResultSet* result_set);

    MySQLResultSetWrapper(std::unique_ptr<sql::ResultSet>) = delete;
    MySQLResultSetWrapper(const MySQLResultSetWrapper&) = delete;
    MySQLResultSetWrapper& operator=(const MySQLResultSetWrapper&) = delete;

    /**
     * @brief Advance the cursor to the next row.
     *
     * @return true if a row is available, false when the end is reached.
     * @throws std::runtime_error if the underlying driver reports an error.
     */
    bool next() override;

    /**
     * @brief Get integer value of a column by name.
     * @param columnName Column name as returned by the driver.
     * @return int Integer value from the current row.
     * @throws std::runtime_error on driver errors or type mismatches.
     */
    int getInt(const std::string& columnName) const override;

    /**
     * @brief Get string value of a column by name.
     * @param columnName Column name as returned by the driver.
     * @return std::string String value from the current row.
     * @throws std::runtime_error on driver errors.
     */
    std::string getString(const std::string& columnName) const override;

    /**
     * @brief Get double value of a column by name.
     * @param columnName Column name as returned by the driver.
     * @return double Double value from the current row.
     * @throws std::runtime_error on driver errors or type mismatches.
     */
    double getDouble(const std::string& columnName) const override;

    /**
     * @brief Get boolean value of a column by name.
     * @param columnName Column name as returned by the driver.
     * @return bool Boolean value from the current row.
     * @throws std::runtime_error on driver errors or type mismatches.
     */
    bool getBoolean(const std::string& columnName) const override;

    /**
     * @brief Test whether the named column contains SQL NULL.
     * @param columnName Column name as returned by the driver.
     * @return true when the column is SQL NULL.
     */
    bool isNull(const std::string& columnName) const override;

    /**
     * @brief Get integer value of a column by 1-based index.
     * @param columnIndex 1-based column index as used by MySQL driver.
     * @return int Integer value from the current row.
     * @throws std::runtime_error on driver errors.
     */
    int getInt(int columnIndex) const override;

    /**
     * @brief Get double value of a column by 1-based index.
     * @param columnIndex 1-based column index as used by MySQL driver.
     * @return double Double value from the current row.
     * @throws std::runtime_error on driver errors.
     */
    double getDouble(int columnIndex) const override;

    /**
     * @brief Get boolean value of a column by 1-based index.
     * @param columnIndex 1-based column index as used by MySQL driver.
     * @return bool Boolean value from the current row.
     * @throws std::runtime_error on driver errors.
     */
    bool getBoolean(int columnIndex) const override;

    /**
     * @brief Test whether the indexed column contains SQL NULL.
     * @param columnIndex 1-based column index as used by MySQL driver.
     * @return true when the column is SQL NULL.
     */
    bool isNull(int columnIndex) const override;

    /**
     * @brief Get string value of a column by 1-based index.
     * @param columnIndex 1-based column index as used by MySQL driver.
     * @return std::string String value from the current row.
     * @throws std::runtime_error on driver errors.
     */
    std::string getString(int columnIndex) const override;
};
