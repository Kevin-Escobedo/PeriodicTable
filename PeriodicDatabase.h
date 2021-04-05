#ifndef PERIODICDATABASE_H
#define PERIODICDATABASE_H
#include "Database.h"

class PeriodicDatabase: public Database
{
public:
	PeriodicDatabase(const char* dbName);
	void createTable();
	void insertElement(const int num, const char* symbol, const char* name, const double weight);
	std::string* getElement(const char* tableName, const int num);
};

#endif /* PERIODICDATABASE_H */
