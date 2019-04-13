#include "../include/db.h"

void TeaDB::db::insert(string tableName, bool create = true) {
    auto table = new TeaDB::table(tableName, name, path);
    tables.insert(std::pair<string, TeaDB::table*>(tableName, table));
    if (create) table->create();
}

void TeaDB::db::create() {
    string command("mkdir " + path + name);
    system(command.c_str());
}