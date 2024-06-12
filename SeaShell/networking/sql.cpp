#include "sql.hpp"

void appendToSettings(std::vector<char>& vec, const string & str) {
    vec.insert(vec.end(), str.begin(), str.end());
    vec.push_back('\0'); // Null-terminate each string
}

void CreateSettingsDB(){
    sqlite3 *db;
    char *errMsg = nullptr;
    int rc;

    rc = sqlite3_open("settings.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        cout << "Opened database successfully" << std::endl;
    }

    const char *createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS settings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            setting TEXT UNIQUE NOT NULL,
            value TEXT NOT NULL
        );
    )";

    // Execute SQL statement to create the table
    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    } else {
        cout << "Table created successfully" << std::endl;
    }

    std::vector<char> settings;
    appendToSettings(settings, "INSERT INTO settings (setting, value) VALUES ('default_color', 'RED');");
    appendToSettings(settings, "INSERT INTO settings (setting, value) VALUES ('folder_color', 'BLUE');");
    appendToSettings(settings, "INSERT INTO settings (setting, value) VALUES ('file_color', 'GREEN');");

    // Execute each SQL statement
    const char *sql = settings.data();
    for (size_t pos = 0; pos < settings.size(); pos += std::strlen(sql) + 1) {
        sql = &settings[pos];
        rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        } else {
            cout << "Inserted data successfully" << std::endl;
        }
    }

    // Close the database
    sqlite3_close(db);
}

void LoadSettingsDB(){
    sqlite3 *db;
    char *errMsg = nullptr;
    int rc;

    rc = sqlite3_open("settings.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        cout << "Opened database successfully" << std::endl;
    }

    const char *selectDataSQL = "SELECT * FROM settings;";

    // Callback function to process the result set
    auto callback = [](void *data, int argc, char **argv, char **azColName) -> int {
        for (int i = 0; i < argc; i++) {
            cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        return 0;
    };

    // Execute SQL statement to select data from the "settings" table
    rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);
}


string SettingValue(const string& settingName){
    sqlite3 *db;
    char *errMsg = nullptr;
    int rc;
    string value;

    rc = sqlite3_open("settings.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return "";
    } else {
        cout << "Opened database successfully" << std::endl;
    }

    // Prepare SQL statement to get the specific setting value
    string sql = "SELECT value FROM settings WHERE setting = ?";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    // Bind the setting name parameter
    rc = sqlite3_bind_text(stmt, 1, settingName.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "";
    }

    // Execute the query and get the value
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return value;
}