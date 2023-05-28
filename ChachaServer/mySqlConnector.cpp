#include "mySqlConnector.h"

mySqlConnector::mySqlConnector()
{
	connect();
}

mySqlConnector::~mySqlConnector()
{
	disconnect();
}

void mySqlConnector::deleteKey(int id)
{
    try {
        _pstmt = _conn->prepareStatement("DELETE FROM ckeys WHERE id = ?");
        _pstmt->setInt(1, id);

    }
    catch (sql::SQLException& e) {
        throw runtime_error(string(e.what()));
    }
}

pair<const char*, const char*> mySqlConnector::getKey(int id)
{
    try {
        const char* key;
        const char* iv;
        _pstmt = _conn->prepareStatement("SELECT * FROM ckeys;");
        _result = _pstmt->executeQuery();
        while (_result->next()) {
            key = _result->getString(2).c_str();
            iv = _result->getString(3).c_str();
            return pair<const char*, const char*>(key, iv);
        } 
    }
    catch (sql::SQLException& e) {
        throw runtime_error(string(e.what()));
    }
}

void mySqlConnector::connect()
{
    try {
        // Read the configuration file
        Config cfg;
        cfg.readFile("config.ini");

        // Get the database connection parameters from the configuration file
        string host = cfg.lookup("mysql.host");
        string user = cfg.lookup("mysql.user");
        string password = cfg.lookup("mysql.password");
        string database = cfg.lookup("mysql.database");


        _driver = get_driver_instance();
        _conn = _driver->connect(host, user, password);
        _conn->setSchema(database);
    }
    catch (sql::SQLException& e) {
        throw std::runtime_error("Error connecting to MySQL: " + string(e.what()));
    }
}

void mySqlConnector::disconnect()
{
    try {
        if (_conn != nullptr) {
            _conn->close();
            delete _conn;
        }
        if (_pstmt != nullptr)
        {
            _pstmt->close();
            delete _pstmt;
        }
    }
    catch (sql::SQLException& e) {
        throw runtime_error("Error disconnecting from MySQL: " + string(e.what()));
    }
}
