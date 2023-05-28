#ifndef MY_SQL_CONNECTOR_H
#define MY_SQL_CONNECTOR_H

#include "AesDecryption.h"
#include <libconfig.h++>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/driver.h>

using namespace std;
using namespace libconfig;

class mySqlConnector
{
public:
	mySqlConnector();
	~mySqlConnector();

	void deleteKey(int id);
	pair<const char*, const char*> getKey(int id);
	void connect();
	void disconnect();
private:

	sql::Driver* _driver;
	sql::Connection* _conn;
	sql::PreparedStatement* _pstmt;
	sql::ResultSet* _result;
};
#endif