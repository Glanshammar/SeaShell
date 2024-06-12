#include "sql.hpp"

static int collectTableNames(void *data, int argc, char **argv, char **azColName) {
    auto *tables = static_cast<std::vector<std::string>*>(data);
    for (int i = 0; i < argc; i++) {
        if (argv[i]) {
            tables->emplace_back(argv[i]);
        }
    }
    return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

void LoadSQLite(Arguments args, Options options){
    sqlite3 *db;
    char *errMsg = nullptr;
    int rc;

    string home = getHomeDirectory();
    string sqldbPath;


    if(args.empty()){
        std::cerr << "No database provided." << std::endl;
        return;
    } else if (args[0] == "chrome") {
        sqldbPath = home + "/AppData/Local/Google/Chrome/User Data/Default/Network/Cookies";
    }

    const char* sqldb = sqldbPath.c_str();

    rc = sqlite3_open(sqldb, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // SQL statement to get table names
    const char *sql = "SELECT name FROM sqlite_master WHERE type='table';";

    // Vector to store table names
    std::vector<std::string> tables;

    // Execute SQL statement to get table names
    rc = sqlite3_exec(db, sql, collectTableNames, &tables, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Retrieved table names successfully" << std::endl;
    }

    // For each table, query all rows and columns
    for (const std::string &table : tables) {
        std::cout << "Table: " << table << std::endl;
        std::string tableQuery = "SELECT * FROM " + table + ";";
        rc = sqlite3_exec(db, tableQuery.c_str(), callback, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    // Close the database
    sqlite3_close(db);
}