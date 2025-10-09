#include "CustomerRepository.h"

// Constructor
CustomerRepository::CustomerRepository(IDatabase& db) : database(db) {}

// Private helper methods
bool CustomerRepository::doesCustomerExist(int id) const {
    auto stmt = database.prepareStatement("SELECT COUNT(*) FROM customers WHERE customer_id=?");
    stmt->setInt(1, id);
    auto result = stmt->executeQuery();
    return result->next() && result->getInt(1) > 0;
}

void CustomerRepository::validateCustomerExists(int customer_id) const {
    if (!doesCustomerExist(customer_id)) {
        throw std::runtime_error("Database Error: Customer " + std::to_string(customer_id) + " doesn't exist!");
    }
}

Customer CustomerRepository::createCustomerFromRow(const IGenericResultSet& result) const {
    return Customer(
        result.getInt("customer_id"),
        result.getString("name"),
        result.getInt("age"),
        result.getString("phone_number"),
        result.getString("email")
    );
}

std::vector<Customer> CustomerRepository::fetchCustomers(std::unique_ptr<IGenericResultSet> result) const {
    std::vector<Customer> customers;
    while (result->next()) {
        customers.emplace_back(createCustomerFromRow(*result));
    }
    return customers;
}
int CustomerRepository::getLastInsertedId()const {
    auto stmt = database.prepareStatement("SELECT LAST_INSERT_ID()");
    auto result = stmt->executeQuery();
    if (result->next()) {
        return result->getInt(1);
    }
    throw std::runtime_error("Database Error: Failed to get last inserted customer id");
}
// CREATE
int CustomerRepository::addCustomer(const Customer& customer) const {
    try {
        auto stmt = database.prepareStatement(
            "INSERT INTO customers (age,name,phone_number,email) VALUES (?,?,?,?)"
        );
        stmt->setInt(1, customer.getAge());
        stmt->setString(2, customer.getName());
        stmt->setString(3, customer.getPhoneNumber());
        stmt->setString(4, customer.getEmail());
        stmt->executeUpdate();
        return getLastInsertedId();
    }
    catch (const std::exception& e) {
        throw std::runtime_error(
            "Database Error: Failed to add customer '" + customer.getName() +
            "' (email: " + customer.getEmail() + ") - " + e.what());
    }
}

// READ
Customer CustomerRepository::getCustomerById(int customer_id) const {
    auto stmt = database.prepareStatement(
        "SELECT * FROM customers WHERE customer_id = ?"
    );
    stmt->setInt(1, customer_id);
    auto result = stmt->executeQuery();
    if (result->next()) {
        return createCustomerFromRow(*result);
    }
    throw std::runtime_error("Database Error: Customer " + std::to_string(customer_id) + " not found!");
}

int CustomerRepository::getNumberOfCustomers() const {
    auto stmt = database.prepareStatement("SELECT COUNT(*) FROM customers");
    auto result = stmt->executeQuery();
    return result->next() ? result->getInt(1) : 0;
}

std::vector<Customer> CustomerRepository::getAllCustomers() const {
    auto stmt = database.prepareStatement("SELECT * FROM customers");
    auto result = stmt->executeQuery();
    return fetchCustomers(std::move(result));
}

// UPDATE
void CustomerRepository::updateCustomerEmail(int customer_id, const std::string& newEmail) const {
    validateCustomerExists(customer_id);
    try {
        auto stmt = database.prepareStatement("UPDATE customers SET email = ? WHERE customer_id=?");
        stmt->setString(1, newEmail);
        stmt->setInt(2, customer_id);
        stmt->executeUpdate();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Database Error: " + std::string(e.what()));

    }
}

void CustomerRepository::updateCustomerPhoneNumber(int customer_id, const std::string& new_phone) const {

    validateCustomerExists(customer_id);
    try {
        auto stmt = database.prepareStatement("UPDATE customers SET phone_number=? WHERE customer_id=?");
        stmt->setString(1, new_phone);
        stmt->setInt(2, customer_id);
        stmt->executeUpdate();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Database Error: " + std::string(e.what()));

    }
}

// DELETE
void CustomerRepository::deleteCustomer(int customer_id) const {
    validateCustomerExists(customer_id);
    auto stmt = database.prepareStatement("DELETE FROM customers WHERE customer_id = ?");
    stmt->setInt(1, customer_id);
    if (!stmt->executeUpdate()) {
        throw std::runtime_error("Database Error: Failed to delete customer " + std::to_string(customer_id));
    }
}
