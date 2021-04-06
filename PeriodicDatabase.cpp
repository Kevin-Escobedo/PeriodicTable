#include "PeriodicDatabase.h"

PeriodicDatabase::PeriodicDatabase(const char* dbName) : Database(dbName)
{

}

void PeriodicDatabase::createTable()
{
    const char* command = "CREATE TABLE IF NOT EXISTS PERIODIC(" \
				"NUM INT PRIMARY KEY NOT NULL, "\
                "SYMBOL TEXT NOT NULL, "\
                "NAME TEXT NOT NULL, "
				"WEIGHT REAL NOT NULL );";

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void PeriodicDatabase::insertElement(const int num, const char* symbol, const char* name, const double weight)
{
	char values[64];
	sprintf(values, "VALUES(%d, '%s', '%s', %7.4f);", num, symbol, name, weight);
	std::string dataValues(values);
	std::string sqlCommand = "INSERT INTO PERIODIC(NUM, SYMBOL, NAME, WEIGHT) ";
	std::string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

std::string* PeriodicDatabase::getElement(const char* tableName, const int num)
{
	results.clear();
	char command[64];
	sprintf(command, "SELECT * FROM %s WHERE NUM=%d", tableName, num);
	std::string tempCommand(command);
	const char* sqlCommand = tempCommand.c_str();

	rc = sqlite3_exec(db, sqlCommand, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		char errMessage[32];
		sprintf(errMessage, "no such table: %s", tableName);
		bool noTable = strcmp(zErrMsg, errMessage) == 0;

		if(!noTable)
		{
			fprintf(stderr, "SQL Error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return nullptr;
		}

		sqlite3_free(zErrMsg);
		return nullptr;
	}

	else
	{
		std::string* data = results[0];
		return data;
	}
}
