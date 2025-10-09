#include "MySQLResultSetWrapper.h"

MySQLResultSetWrapper::MySQLResultSetWrapper(sql::ResultSet* result_set)
    : result(result_set)
{
    if (!result) {
        throw std::invalid_argument("ResultSet cannot be null");
    }
}

bool MySQLResultSetWrapper::next() { return result->next(); }
int MySQLResultSetWrapper::getInt(const std::string& columnName) const { return result->getInt(columnName); }
std::string MySQLResultSetWrapper::getString(const std::string& columnName) const { return result->getString(columnName); }
double MySQLResultSetWrapper::getDouble(const std::string& columnName) const { return result->getDouble(columnName); }
bool MySQLResultSetWrapper::getBoolean(const std::string& columnName) const { return result->getBoolean(columnName); }
bool MySQLResultSetWrapper::isNull(const std::string& columnName) const { return result->isNull(columnName); }

int MySQLResultSetWrapper::getInt(int columnIndex) const { return result->getInt(columnIndex); }
double MySQLResultSetWrapper::getDouble(int columnIndex) const { return result->getDouble(columnIndex); }
bool MySQLResultSetWrapper::getBoolean(int columnIndex) const { return result->getBoolean(columnIndex); }
bool MySQLResultSetWrapper::isNull(int columnIndex) const { return result->isNull(columnIndex); }
std::string MySQLResultSetWrapper::getString(int columnIndex) const { return result->getString(columnIndex); }
