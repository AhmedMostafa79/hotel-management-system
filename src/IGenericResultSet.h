#pragma once
#include <string>
#include <memory>

/**
 * @file IGenericResultSet.h
 * @brief Generic read-only result-set adapter used by repository code.
 *
 * This interface abstracts the driver-specific result set returned by the
 * SQL driver and exposes a small, safe set of accessors that repository
 * code can use when mapping rows to domain objects. Implementations are
 * expected to translate driver exceptions into std::runtime_error or similar
 * so callers can handle errors uniformly.
 */
class IGenericResultSet {
public:
    virtual ~IGenericResultSet() = default;
    /**
     * @brief Advance the cursor to the next row in the result set.
     *
     * Typical usage:
     * @code
     * while (rs->next()) {
     *   int id = rs->getInt("id");
     * }
     * @endcode
     *
     * @return true if a row is available, false when the end of the set is reached.
     * @throws std::runtime_error on underlying driver errors.
     */
    virtual bool next() = 0;

    // Column access by name
    /**
     * @brief Get integer value of a column by name.
     * @param columnName Name of the column to read (case-sensitive depending on driver).
     * @return int Integer value stored in the column.
     * @throws std::runtime_error on driver errors or type mismatches.
     */
    virtual int getInt(const std::string& columnName) const = 0;

    /**
     * @brief Get double value of a column by name.
     * @param columnName Name of the column to read.
     * @return double Double value stored in the column.
     * @throws std::runtime_error on driver errors or type mismatches.
     */
    virtual double getDouble(const std::string& columnName) const = 0;

    /**
     * @brief Get string value of a column by name.
     * @param columnName Name of the column to read.
     * @return std::string String value stored in the column.
     * @throws std::runtime_error on driver errors.
     */
    virtual std::string getString(const std::string& columnName) const = 0;

    /**
     * @brief Get boolean value of a column by name.
     * @param columnName Name of the column to read.
     * @return bool Boolean value stored in the column.
     * @throws std::runtime_error on driver errors or type mismatches.
     */
    virtual bool getBoolean(const std::string& columnName) const = 0;

    /**
     * @brief Test whether the named column contains SQL NULL.
     * @param columnName Name of the column.
     * @return true when the column is SQL NULL.
     */
    virtual bool isNull(const std::string& columnName) const = 0;

    // Column access by 1-based index
    /**
     * @brief Get integer value of a column by 1-based index.
     * @param columnIndex 1-based column index as used by most SQL drivers.
     * @return int Integer value stored in the column.
     * @throws std::runtime_error on driver errors.
     */
    virtual int getInt(int columnIndex) const = 0;

    /**
     * @brief Get double value of a column by 1-based index.
     * @param columnIndex 1-based column index.
     * @return double Double value stored in the column.
     * @throws std::runtime_error on driver errors.
     */
    virtual double getDouble(int columnIndex) const = 0;

    /**
     * @brief Get boolean value of a column by 1-based index.
     * @param columnIndex 1-based column index.
     * @return bool Boolean value stored in the column.
     */
    virtual bool getBoolean(int columnIndex) const = 0;

    /**
     * @brief Test whether the indexed column contains SQL NULL.
     * @param columnIndex 1-based column index.
     * @return true when the column is SQL NULL.
     */
    virtual bool isNull(int columnIndex) const = 0;

    /**
     * @brief Get string value of a column by 1-based index.
     * @param columnIndex 1-based column index.
     * @return std::string String value stored in the column.
     */
    virtual std::string getString(int columnIndex) const = 0;
};
