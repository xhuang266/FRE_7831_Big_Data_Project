//
//  Database.hpp
//  finalprj_Pair-Trading
//
//  Created by Deyang Van on 4/28/22.
//
//

#include <string>
#include "sqlite3.h"
#include "Stock.hpp"
#include "Util.hpp"


using namespace std;

int OpenDatabase(const char* database_name, sqlite3* & db);

int DropTable(sqlite3 * db, const char* sql_stmt);

int ExecuteSQL(sqlite3* db, const char* sql_stmt);

int ShowTable(sqlite3* db, const char* sql_stmt);

int InsertTable(sqlite3* db, bool IsStockOne, const Stock &stock);

void CloseDatabase(sqlite3* db);



int Create_PairTable(const vector<StockPairPrices>& all_Pairs,sqlite3* db);
int Create_PairOneTwoPricesTable(sqlite3 * &db);
int Create_PairPricesTable(sqlite3* & db);
