#include <iostream>
//#include "base64-master/base64.h"
#include "include/db.h"

using std::string;

int main() {
    TeaDB::db db("test");
//    db.create();
    db.insert("test", true);
    auto table = db.tab("test");
////    std::cout << table << std::endl;
    table->insert("name: \"TeaDB\", language: \"c++\", level: 5");
//    table->insert("best_number: 5");
    return 0;
}