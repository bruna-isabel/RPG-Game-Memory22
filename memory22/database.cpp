#include "sqlite3.h"
#include "database.h"
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <fstream>


Database::Database(std::string DatabaseFileName)
{
    //Connecting to the database
    std::string fileNamestr = DatabaseFileName + ".db";
    //sqlite function only takes char* as input so I convert the string
    const char *fileName = fileNamestr.c_str();
    rc = sqlite3_open(fileName, &db);
}

Database::~Database()
{
    sqlite3_close(db);
}


// METHODS //


int Database::query(std::string commandstr)
{
    /**
     * Executes any SQL commands(other than SELECT commands) on database class objects 
     * Input is an SQL command string
     **/
    
    //convert string to const char pointer to make it work with sqlite api interface
    const char *command = commandstr.c_str();
    rc = sqlite3_exec(db, command, NULL, NULL, NULL);
    return rc;
    
    
}



std::map<std::string, std::string> Database::selectQuery(std::string tableName, std::string where )  //setting a value for 'where' in the header file so it defaults to an empty string and we dont have to pass the argument every time
{
    /**
     * Extracts data from an SQLite database class object
     * Input is an SQL SELECT command string
     * Output is a <string, string> MAP where the key is the column name
     * everything is a string so int datatypes need to be converted later on using checkIfInt function
     **/
    std::string commandstr;
    if(tableName == "player")
    {
        commandstr = "SELECT * FROM Player";
    }
    else if(tableName == "mobs")
    {
        commandstr = "SELECT * FROM Monsters WHERE MonsterName = '" + where + "';";
    }
    else if(tableName == "items")
    {
        commandstr = "SELECT * FROM Items WHERE ItemName = '" + where + "';";
    }
    else if(tableName == "npcs")
    {
        commandstr = "SELECT * FROM NPC WHERE NpcName = '" + where + "';";
    }
    else if(tableName == "quests")
    {
        commandstr = "SELECT * FROM Quests WHERE QuestName = '" + where + "';";
    }
    else if(tableName == "inventory")
    {
        commandstr = "SELECT * FROM Inventory WHERE Position = '" + where + "';";
    }
    //std::cout<<commandstr<<std::endl;
    //convert string to const char pointer to make it work with sqlite api interface
    const char *command = commandstr.c_str();
    sqlite3_prepare_v2(db, command, -1, &stmt, NULL);
    int cols = sqlite3_column_count(stmt);
    while ( sqlite3_step(stmt) == SQLITE_ROW)
    {
        for(int col = 0; col < cols; col++)
        {
            //convert the const unsigned char the column_text function produces into a string (reinterpret_cast)
            std::string datastr = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
            std::string colnamesstr = std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, col)));
            data.push_back(datastr);
            colNames.push_back(colnamesstr);
        }
    }
    std::map<std::string, std::string> dataMap;
    for(int i = 0; i<colNames.size(); i++)
    {
        dataMap[colNames[i]] = data[i];
    }
    return dataMap;
}


void Database::presetGameData()
{
    /**
     * Reads SQL commands from a text file and executes them to create the initial database
    **/
    std::string command;
    std::ifstream gameDataSQL;
    gameDataSQL.open("PresetData.txt");
    while(!gameDataSQL.eof())
    {
        getline(gameDataSQL, command);
        if(command == "")
        {
            continue;
        }
        query(command);
    }
    gameDataSQL.close();
}

void Database::deleteData()
{
	//drop all tables
	query("DROP TABLE Player;");
	query("DROP TABLE Monsters;");
	query("DROP TABLE NPC;");
	query("DROP TABLE Items;");
	query("DROP TABLE Quest;");
	query("DROP TABLE Inventory;");
}




