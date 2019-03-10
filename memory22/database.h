#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "sqlite3.h"


class Database
{
    private:
    public:
    int rc;
    char *sql;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::vector<std::string> data;
    std::vector<std::string> colNames;

    Database(std::string DatabaseFileName);
    ~Database();
    int query(std::string commandstr);
    std::map<std::string, std::string> selectQuery(std::string tableName, std::string where = "");
    void presetGameData();
};
