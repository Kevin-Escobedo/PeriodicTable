#ifndef PERIODICDATABASE_H
#define PERIODICDATABASE_H
#include "Database.h"

class PeriodicDatabase: public Database
{
public:
	PeriodicDatabase(const char* dbName);
	void createTable();
	void insertElement(const int num, const char* symbol, const char* name, const double weight);
};

#endif /* PERIODICDATABASE_H */
