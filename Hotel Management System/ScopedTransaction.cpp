#include "ScopedTransaction.h"
ScopedTransaction:: ScopedTransaction(IDatabase& db) :database(db), commited(false) {
	database.beginTransaction();
}
void ScopedTransaction::commit() {
	database.commitTransaction();
	commited = true;
}
ScopedTransaction:: ~ScopedTransaction() {
	if (!commited && database.isTransactionActive()) {
		database.rollbackTransaction();
	}
}