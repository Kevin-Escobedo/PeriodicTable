#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <ctime>
#include <vector>

class Database
{
protected:
	sqlite3* db;
	char* zErrMsg = nullptr;
	int rc;
	bool isOpen = false;
	inline static std::vector<std::string*> results;
public:
	Database(const char* databaseName);
	Database(const Database& d);
	~Database();
	Database& operator =(const Database& d);
	int length(const char* tableName);
	void clearMemory();
	void close();
protected:
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	const char* currentTime();
};

#endif /* DATABASE_H */
