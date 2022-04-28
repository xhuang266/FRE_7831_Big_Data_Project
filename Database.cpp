//
//  Database.cpp
//  lab_marketData
//
//  Created by Deyang Van on 4/10/22.
//

#include "Database.hpp"
#include <iostream>
#include <string>

using namespace std;

int OpenDatabase(const char* database_name, sqlite3* & db)
{
    int rc = 0;
    rc = sqlite3_open(database_name, &db);
    if (rc)
    {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }
    else
    {
        std::cout << "Opened " << database_name << std::endl;
    }

    std::string foreign_ley_check = "PRAGMA foreign_keys = ON";
    if (sqlite3_exec(db, foreign_ley_check.c_str(), 0, 0, 0) != SQLITE_OK) {
        std::cout << "SQLite fails in setting foreign key check" << std::endl;
        sqlite3_close(db);
        return -1;
    }

    return 0;
}

int DropTable(sqlite3 * db, const char* sql_stmt)
{
    if (sqlite3_exec(db, sql_stmt, 0, 0, 0) != SQLITE_OK) {
        std::cout << "SQLite can not drop table" << std::endl;
        sqlite3_close(db);
        return -1;
    }
    return 0;
}

int ExecuteSQL(sqlite3* db, const char* sql_stmt)
{
    int rc = 0;
    char* error = nullptr;
    rc = sqlite3_exec(db, sql_stmt, NULL, NULL, &error);
    if (rc)
    {
        std::cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_free(error);
        return -1;
    }
    return 0;
}

int ShowTable(sqlite3* db, const char* sql_stmt)
{
    int rc = 0;
    char* error = nullptr;
    char** results = NULL;
    int rows, columns;
    sqlite3_get_table(db, sql_stmt, &results, &rows, &columns, &error);
    if (rc)
    {
        std::cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_free(error);
        return -1;
    }
    else
    {
        // Display Table
        for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
        {
            for (int colCtr = 0; colCtr < columns; ++colCtr)
            {
                // Determine Cell Position
                int cellPosition = (rowCtr * columns) + colCtr;

                // Display Cell Value
                std::cout.width(12);
                std::cout.setf(std::ios::left);
                std::cout << results[cellPosition] << " ";
            }

            // End Line
            std::cout << std::endl;

            // Display Separator For Header
            if (0 == rowCtr)
            {
                for (int colCtr = 0; colCtr < columns; ++colCtr)
                {
                    std::cout.width(12);
                    std::cout.setf(std::ios::left);
                    std::cout << "~~~~~~~~~~~~ ";
                }
                std::cout << std::endl;
            }
        }
    }
    sqlite3_free_table(results);
    return 0;
}

void CloseDatabase(sqlite3* db)
{
    sqlite3_close(db);
}

string sql_stmt_insert_Daily(string symbol, string date, float open, float high, float low, float close, float adjusted_close, int volume){
    // "INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
    string sql_stmt = string("INSERT INTO ")
        + "DailyTrades "
        + "VALUES("
        + "'"+ symbol + "'"+ ","
        + "'"+ date + "'"+ ","
        + to_string(open) + ","
        + to_string(high) + ","
        + to_string(low) + ","
        + to_string(close) + ","
        + to_string(adjusted_close) + ","
        + to_string(volume)
        + ");";
    
    return sql_stmt;
}



string sql_stmt_insert_Intraday(string symbol, string date, string timestamp, float open, float high, float low, float close, int volume){
    string sql_stmt = string("INSERT INTO ")
        + "IntradayTrades "
        + "VALUES("
        + "'"+ symbol + "'"+ ","
        + "'"+ date + "'"+ ","
        + "'"+ timestamp + "'"+ ","
        + to_string(open) + ","
        + to_string(high) + ","
        + to_string(low) + ","
        + to_string(close) + ","
        + to_string(volume)
        + ");";
    
    return sql_stmt;
}