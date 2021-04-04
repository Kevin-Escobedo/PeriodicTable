#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <ctime>

class Database
{
protected:
	sqlite3* db;
	char* zErrMsg = nullptr;
	int rc;
	bool isOpen = false;
public:
	Database(const char* databaseName);
	Database(const Database& d);
	~Database();
	Database& operator =(const Database& d);
	void close();
protected:
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	int length(const char* tableName);
	const char* currentTime();
};

#endif /* DATABASE_H */
