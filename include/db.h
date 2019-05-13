#ifndef TEADB_DB_H
#define TEADB_DB_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>
#include "table.h"
#include "reader.h"
#include "high_precision.h"
using std::string;
using std::map;

namespace TeaDB {
    class db {
    public:
        db(string n, string p = "/usr/local/TeaDB/") : name(n), path(p) { }
        void create();
        void insert(string, bool);
        inline table* tab(string name) {
            auto iter = tables.find(name);
            if (iter == tables.end()) return nullptr;
            return iter->second;
        }
    private:
        string name;
        string path;
        map<string, TeaDB::table*> tables;
    };
}

#endif //TEADB_DB_H
