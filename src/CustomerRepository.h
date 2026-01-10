#pragma once
#include "IDatabase.h"
#include "Customer.h"
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * @file CustomerRepository.h
 * @brief Persistence operations for Customer entities.
 *
 * The CustomerRepository implements CRUD operations for Customer objects using the
 * provided IDatabase adapter. All methods operate on the underlying
 * database and translate rows into concrete Customer object.
 */
class CustomerRepository {
    IDatabase& database; ///< Database adapter used to perform SQL operations.

    // Helper methods (private)

    /**
     * @brief Construct a Customer object from a result row.
     * @param result Result row abstraction to read fields from.
     * @return Customer Constructed customer value.
     */
    Customer createCustomerFromRow(const IGenericResultSet& result) const;

    /**
     * @brief Convert a result set into a vector of Customer objects.
     * @param result Owned result set returned from a query.
     * @return std::vector<Customer> List of customers.
     */
    std::vector<Customer> fetchCustomers(std::unique_ptr<IGenericResultSet> result) const;

    /**
     * @brief Read last inserted id produced by the DB for auto-increment keys.
     * @return int Last inserted id value.
     */
    int getLastInsertedId() const;

public:
    /**
     * @brief Construct repository using the provided database adapter.
     * @param db Database adapter reference.
     */
    CustomerRepository(IDatabase& db);

    /**
     * @brief Check whether a customer with the given id exists.
     * @param id Customer id to check.
     * @return true if the customer exists, false otherwise.
     */
    bool doesCustomerExist(int id) const;

    /**
     * @brief Validate the existence of a customer and throw if missing.
     * @param customer_id Customer id to validate.
     * @throws std::invalid_argument if the customer does not exist.
     */
    void validateCustomerExists(int customer_id) const;

    // CREATE
    /**
     * @brief Insert a new customer and return the created id.
     * @param customer Customer value to persist.
     * @return int Inserted customer id.
     */
    int addCustomerAndGetId(const Customer& customer) const;

    // READ
    /**
     * @brief Load a customer by id.
     * @param customer_id Customer id to load.
     * @return Customer Loaded customer value.
     */
    Customer getCustomerById(int customer_id) const;

    /**
     * @brief Count customers stored in the system.
     * @return int Number of customers.
     */
    int getNumberOfCustomers() const;

    /**
     * @brief Retrieve all customers.
     * @return std::vector<Customer> List of all customers.
     */
    std::vector<Customer> getAllCustomers() const;

    // UPDATE
    /**
     * @brief Update a customer's email address.
     * @param customer_id Customer id to update.
     * @param newEmail New email value.
     */
    void updateCustomerEmail(int customer_id, const std::string& newEmail) const;

    /**
     * @brief Update a customer's phone number.
     * @param customer_id Customer id to update.
     * @param new_phone New phone number value.
     */
    void updateCustomerPhoneNumber(int customer_id, const std::string& new_phone) const;

    // DELETE
    /**
     * @brief Delete a customer by id.
     * @param customer_id Customer id to remove.
     */
    void deleteCustomer(int customer_id) const;
};
