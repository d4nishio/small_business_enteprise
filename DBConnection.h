#pragma once
#ifndef DBConnection_H
#define DBConnection_H

#include <mysql/jdbc.h>
#include <string>

class DBConnection
{
public:
	DBConnection();
	~DBConnection();
	void prepareStatement(std::string query); // this where sql query is inserted
	sql::PreparedStatement* stmt;
	sql::ResultSet* res;
	void QueryStatement(); // have no result
	void QueryResult(); // has result
	int getGeneratedId();

private:
	sql::Connection* connection;

};

#endif // !DBConnection_H