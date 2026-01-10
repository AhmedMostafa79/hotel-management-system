#pragma once
#include "IDatabase.h"
class ScopedTransaction{
private:
	IDatabase& database;
	bool commited;
public:
	explicit ScopedTransaction(IDatabase& db);
	void commit();
	~ScopedTransaction();
	ScopedTransaction(const ScopedTransaction&) = delete;
	ScopedTransaction& operator=(const ScopedTransaction&) = delete;
};