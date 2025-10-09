#include "MySQLStatementWrapper.h"

MySQLStatementWrapper::MySQLStatementWrapper(sql::PreparedStatement* statement)
    : stmt(statement)
{
    if (!stmt) throw std::invalid_argument("PreparedStatement cannot be null");
}

void MySQLStatementWrapper::setInt(int paramIndex, int value) { stmt->setInt(paramIndex, value); }
void MySQLStatementWrapper::setString(int paramIndex, const std::string& value) { stmt->setString(paramIndex, value); }
void MySQLStatementWrapper::setDouble(int paramIndex, double value) { stmt->setDouble(paramIndex, value); }
void MySQLStatementWrapper::setBoolean(int paramIndex, bool value) { stmt->setBoolean(paramIndex, value); }

bool MySQLStatementWrapper::execute() { return stmt->execute(); }
int MySQLStatementWrapper::executeUpdate() { return stmt->executeUpdate(); }
std::unique_ptr<IGenericResultSet> MySQLStatementWrapper::executeQuery() const {
    return std::make_unique<MySQLResultSetWrapper>(stmt->executeQuery());
}
void MySQLStatementWrapper::clearParameters() { stmt->clearParameters(); }
