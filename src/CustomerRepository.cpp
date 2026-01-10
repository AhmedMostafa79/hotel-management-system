#include "CustomerRepository.h"
#include "ScopedTransaction.h"
// Constructor
CustomerRepository::CustomerRepository(IDatabase& db) : database(db) {}

// Private helper methods


void CustomerRepository::validateCustomerExists(int customer_id) const {
    auto stmt = database.prepareStatement("SELECT 1 FROM customers WHERE customer_id=?");
    stmt->setInt(1, customer_id);
    auto result = stmt->executeQuery();
    if (!result->next()) {
        throw std::runtime_error("Customer " + std::to_string(customer_id) + " doesn't exist!");
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
//int CustomerRepository::getLastInsertedId()const {
//    auto stmt = database.prepareStatement("SELECT LAST_INSERT_ID()");
//    auto result = stmt->executeQuery();
//    if (result->next()) {
//        return result->getInt(1);
//    }
//    throw std::runtime_error("Database Error: Failed to get last inserted customer id");
//}
// CREATE
int CustomerRepository::addCustomerAndGetId(const Customer& customer) const {
        ScopedTransaction transaction(database);

        auto stmt = database.prepareStatement(
            "INSERT INTO customers (age,name,phone_number,email) VALUES (?,?,?,?)"
        );
        stmt->setInt(1, customer.getAge());
        stmt->setString(2, customer.getName());
        stmt->setString(3, customer.getPhoneNumber());
        stmt->setString(4, customer.getEmail());
        stmt->executeUpdate();
        int customer_id = database.getLastInsertID();
        transaction.commit();
        return customer_id;
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
    throw std::runtime_error("Customer " + std::to_string(customer_id) + " not found!");
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

    ScopedTransaction transaction(database);
    validateCustomerExists(customer_id);
    auto stmt = database.prepareStatement("UPDATE customers SET email = ? WHERE customer_id=?");
    stmt->setString(1, newEmail);
    stmt->setInt(2, customer_id);
    stmt->executeUpdate();

    transaction.commit();
}

void CustomerRepository::updateCustomerPhoneNumber(int customer_id, const std::string& new_phone) const {

    ScopedTransaction transaction(database);

    validateCustomerExists(customer_id);
    auto stmt = database.prepareStatement("UPDATE customers SET phone_number=? WHERE customer_id=?");
    stmt->setString(1, new_phone);
    stmt->setInt(2, customer_id);
    stmt->executeUpdate();

    transaction.commit();
}

// DELETE
void CustomerRepository::deleteCustomer(int customer_id) const {
    ScopedTransaction transaction(database);

    validateCustomerExists(customer_id);
    auto stmt = database.prepareStatement("DELETE FROM customers WHERE customer_id = ?");
    stmt->setInt(1, customer_id);
    stmt->executeUpdate();

    transaction.commit();
}
