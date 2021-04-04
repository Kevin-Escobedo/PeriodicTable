#include "Database.h"

Database::Database(const char* databaseName)
:db(), rc()
{
	rc = sqlite3_open(databaseName, &db);
	if(rc)
	{
		fprintf(stderr, "Unable to open database");
	}

	else
	{
		isOpen = true;
	}
}

Database::Database(const Database& d)
:db(d.db), rc(d.rc), isOpen(d.isOpen)
{

}

Database::~Database()
{
	if(isOpen)
	{
		sqlite3_close(db);
		isOpen = false;
	}
}

Database& Database::operator =(const Database& d)
{
	db = d.db;
	rc = d.rc;
	isOpen = d.isOpen;

	return *this;
}

void Database::close()
{
	if(isOpen)
	{
		sqlite3_close(db);
		isOpen = false;
	}
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	//int* c = (int*)NotUsed;
	//*c = atoi(argv[0]);

	std::string* row = new std::string[argc];

	for(int i = 0; i < argc; i++)
	{
		row[i] += argv[i];
	}

	results.push_back(row);
	bool debug = false;

	if(debug)
	{
		std::cout<<NotUsed<<std::endl;

		for(int i = 0; i < argc; i++)
		{
			printf("%s = %s\n", azColName[i], argv[1] ? argv[i] : "NULL");
		}

		printf("\n");
	}

	return 0;
}

int Database::length(const char* tableName)
{
	results.clear();
	char command[64];
	sprintf(command, "SELECT COUNT(*) FROM %s", tableName);
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
			return -1;
		}

		sqlite3_free(zErrMsg);
		return 0;
	}

	else
	{
		int count = atoi(results[0][0].c_str());
		clearMemory();
		return count;
	}
}

const char* Database::currentTime()
{
	time_t t = time(nullptr);
	tm* now = localtime(&t);
	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;
	int hour = now->tm_hour;
	int minute = now->tm_min;
	int second = now->tm_sec;

	char* buf = new char[64];
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
	return buf;
}

void Database::clearMemory()
{
	int limit = results.size();
	for(int i = 0; i < limit; i++)
	{
		delete[] results[i];
	}
}