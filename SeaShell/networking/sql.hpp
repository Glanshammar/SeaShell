#pragma once

#include "../global.hpp"
#include "../files/filesystem.hpp"
#ifdef USE_MYSQL
#include "mysql.h"
#endif

class MySQLDatabase {
public:
    MySQLDatabase(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname);
    ~MySQLDatabase();

    bool connect();
    void disconnect();
    bool executeQuery(const std::string& query);

private:
    std::string host;
    std::string user;
    std::string password;
    std::string dbname;
};